//
// Created by ctrlz on 2024/7/5.
//

#ifndef REACTORSERVER_CONNECTION_H
#define REACTORSERVER_CONNECTION_H
#include <netinet/in.h>
#include <memory>
#include <atomic>
#include <string>
#include <chrono>
#include "mpsc.h"

class SendMessage {
public:
    SendMessage(char *msgData, int len) {
        msg_ = std::string(msgData, len);
    }

private:
    std::string msg_;
};

class Connection {
public:
    Connection(int socketFd, sockaddr_in remoteAddr);

    ~Connection();

    void send(char *msgData, int len);

    void close(bool isForce = false);

    bool isClosed();

    unsigned int getConnId() const {
        return connId_;
    }
    
    Connection(const Connection &) = delete;
    Connection &operator=(const Connection &) = delete;

private:
    unsigned int connId_;
    int socketFd_;
    sockaddr_in remoteAddr_;
    std::atomic<bool> isClose_;
    std::shared_ptr<Container<SendMessage>> buffer_;
    std::chrono::system_clock::time_point timeStamp_;
};


#endif //REACTORSERVER_CONNECTION_H
