//
// Created by ctrlz on 2024/7/8.
//

#include "PidAllocator.h"

unsigned int PidAllocator::alloc() {
    std::unique_lock<std::mutex> lock(modifyMutex_);
    if (!recycled_.empty()) {
        auto ans = recycled_.back();
        recycled_.pop_back();
        return ans;;
    }
    current_++;
    return current_ - 1;
}

void PidAllocator::dealloc(unsigned int id) {

}

PidAllocator &PidAllocator::getInstance() {
    static PidAllocator instance;
    return instance;
}

PidAllocator::PidAllocator() {
    current_ = 1;
}

unsigned int pidAlloc() {
    return PidAllocator::getInstance().alloc();
}

void pidDealloc(unsigned int pid) {
    PidAllocator::getInstance().dealloc(pid);
}