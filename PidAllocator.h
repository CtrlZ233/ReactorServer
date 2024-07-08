//
// Created by ctrlz on 2024/7/8.
//

#ifndef REACTORSERVER_PIDALLOCATOR_H
#define REACTORSERVER_PIDALLOCATOR_H

#include <vector>
#include <mutex>

class PidAllocator {
public:
    static PidAllocator& getInstance();

    unsigned int alloc();

    void dealloc(unsigned int id);

    PidAllocator(PidAllocator &other) = delete;

    PidAllocator operator = (PidAllocator &other) = delete;

private:

    PidAllocator();

    unsigned int current_;
    std::vector<unsigned int> recycled_;
    std::mutex modifyMutex_;

};

unsigned int pidAlloc();

void pidDealloc(unsigned int);

#endif //REACTORSERVER_PIDALLOCATOR_H
