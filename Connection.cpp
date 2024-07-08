//
// Created by ctrlz on 2024/7/5.
//

#include "Connection.h"
#include "PidAllocator.h"
void Connection::close(bool isForce) {

}

void Connection::send(char *msgData, int len) {
    if (isClosed()) {
        return;
    }
    SendMessage msg(msgData, len);
    buffer_->produce(msg);
}

Connection::Connection(int socketFd, sockaddr_in remoteAddr) : socketFd_(socketFd), remoteAddr_(remoteAddr), isClose_(false) {
    connId_ = pidAlloc();
    buffer_ = std::make_shared<MPSCContainer<SendMessage>>();
    timeStamp_ = std::chrono::system_clock::now();
}

Connection::~Connection() {
    isClose_.store(true, std::memory_order::seq_cst);
    close(socketFd_);
    pidDealloc(connId_);
}

bool Connection::isClosed() {
    return isClose_.load(std::memory_order::relaxed);
}
