//
// Created by ctrlz on 2024/7/8.
//

#ifndef REACTORSERVER_TCPSERVERAPI_H
#define REACTORSERVER_TCPSERVERAPI_H

#include <vector>
#include <memory>
#include "TcpServerSpi.h"
#include "EpollServer.h"

class TcpServerApi {
public:
    explicit TcpServerApi(int workerNum = 1);

    void registerSpi(TcpServerSpi *spi);

    bool bindAddress(sockaddr_in serverAddr);

    bool run();
private:
    std::vector<std::shared_ptr<EpollServer>> workers_;
    TcpServerSpi *spi_;
    const int workerNum_;
    sockaddr_in serverAddr_;
    int listenFd_;

};


#endif //REACTORSERVER_TCPSERVERAPI_H
