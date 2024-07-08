//
// Created by ctrlz on 2024/7/6.
//

#ifndef REACTORSERVER_EPOLLSERVER_H
#define REACTORSERVER_EPOLLSERVER_H

#include <vector>
#include <thread>

#include "Connection.h"

class EpollServer {
public:
    explicit EpollServer(int worker_id);

    EpollServer(const EpollServer &) = delete;

    EpollServer &operator=(const EpollServer &) = delete;

    void registerConn(int socketFd, std::shared_ptr<Connection> conn);

//    void unregisterConn(std::shared_ptr<Connection> conn);
private:
    std::thread th_;
    int worker_id_;
    std::vector<std::shared_ptr<Connection>> conns_;
};


#endif //REACTORSERVER_EPOLLSERVER_H
