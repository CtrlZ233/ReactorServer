#include <map>
#include <set>
#include <memory>
#include <iostream>
#include <functional>

class TimerNode;


class TimerHeap {
public:
    void getTop();

    std::shared_ptr<TimerNode> addTimer(int timeStamp, Task t);
    
    void update(std::shared_ptr<TimerNode> node);
    

    std::set<std::shared_ptr<TimerNode>> heap;
    int currentTimeStamp_;
};

using Task = std::function<void()>;

class TimerNode : public std::enable_shared_from_this<TimerNode> {
public:

    TimerNode(int timeStamp, Task t);
    void update(int timeStamp) {
        timeStamp_ = timeStamp;
        auto h = heap.lock();
        h->update(shared_from_this());
    }
    
    int timeStamp_;
    std::weak_ptr<TimerHeap> heap;
    std::set<std::shared_ptr<TimerNode>>::iterator iter;
    Task task;
    ~TimerNode() {
        std::cout << "byebye" << std::endl;
    }

};

void TimerHeap::getTop() {
    if(heap.empty()) {
        return;
    }
    auto node = *heap.begin();
    if (currentTimeStamp_ > node->timeStamp_) {
        heap.erase(heap.begin());
        node->task();
    }
}

std::shared_ptr<TimerNode> TimerHeap::addTimer(int timeStamp, Task t) {
    auto node = std::make_shared<TimerNode>();
    heap.insert(node);
    return node;
}

void TimerHeap::update(std::shared_ptr<TimerNode> node) {
        if (heap.find(node) != heap.end()) {
            heap.erase(node->iter);
        }
        auto p = heap.insert(node);
        node->iter = p.first;
    }


TimerHeap heap;



int main() {
    auto node = heap.addTimer(1);
    heap.getTop();
    if (sn == nullptr) {
        std::cout << "good" << std::endl;
    }
}