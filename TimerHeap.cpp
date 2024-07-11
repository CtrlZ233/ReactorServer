#include <map>
#include <set>
#include <memory>
#include <iostream>

class TimerNode;


class TimerHeap {
public:
    void getTop();

    std::weak_ptr<TimerNode> addTimer(int timeStamp);
    
    void update(std::shared_ptr<TimerNode> node);
    

    std::set<std::shared_ptr<TimerNode>> heap;
};


class TimerNode : public std::enable_shared_from_this<TimerNode> {
public:
    void update(int timeStamp) {
        timeStamp_ = timeStamp;
        auto h = heap.lock();
        h->update(shared_from_this());
    }
    
    int timeStamp_;
    std::weak_ptr<TimerHeap> heap;
    std::set<std::shared_ptr<TimerNode>>::iterator iter;
    ~TimerNode() {
        std::cout << "byebye" << std::endl;
    }

};

void TimerHeap::getTop() {
    if(heap.empty()) {
        return;
    }
    heap.erase(heap.begin());
}

std::weak_ptr<TimerNode> TimerHeap::addTimer(int timeStamp) {
    auto node = std::make_shared<TimerNode>();
    heap.insert(node);
    return node;
}

void TimerHeap::update(std::shared_ptr<TimerNode> node) {
        heap.erase(node->iter);
        auto p = heap.insert(node);
        node->iter = p.first;
    }


TimerHeap heap;



int main() {
    auto node = heap.addTimer(1);
    heap.getTop();
    auto sn = node.lock();
    if (sn == nullptr) {
        std::cout << "good" << std::endl;
    }
}