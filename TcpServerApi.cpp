//
// Created by ctrlz on 2024/7/8.
//

#include "TcpServerApi.h"
#include "spdlog/spdlog.h"

TcpServerApi::TcpServerApi(int workerNum) : workerNum_(workerNum), spi_(nullptr) {
    listenFd_ = socket(AF_INET, SOCK_STREAM, 0);
    if(listenFd_ == -1) {
        spdlog::error("socket create fail");
        exit(-1);
    }
    workers_ = std::vector<std::shared_ptr<EpollServer>>(workerNum);
}

void TcpServerApi::registerSpi(TcpServerSpi *spi) {
    spi_ = spi;
}

bool TcpServerApi::bindAddress(sockaddr_in serverAddr) {
    serverAddr_ = serverAddr;
    if (bind(listenFd_, (sockaddr *)&serverAddr_, sizeof(serverAddr)) != 0) {
        spdlog::error("bind failed \n");
        return false;
    }
    return true;
}

bool TcpServerApi::run() {
    if (listen(listenFd_, 5) != 0) {
        spdlog::error("Listen failed\n");
        close(listenFd_);
        return false;
    }

    for (int i = 0; i < workerNum_; ++i) {
        workers_[i] = std::make_shared<EpollServer>(i);
    }
    int clientFd;
    socklen_t len = 0;
    sockaddr_in remoteAddr {};
    while (true) {
        if ((clientFd = accept(listenFd_, (sockaddr *)&remoteAddr, &len)) < 0) {
            spdlog::error("accept socket error: %s(errno: %d)", strerror(errno), errno);
            return false;
        }
        auto conn = std::make_shared<Connection>(clientFd, remoteAddr);
        unsigned int worker_id = conn->getConnId() % workerNum_;
        workers_[worker_id]->registerConn(clientFd, conn);
    }
}
