//
// Created by ctrlz on 2024/7/8.
//

#ifndef REACTORSERVER_TCPSERVERSPI_H
#define REACTORSERVER_TCPSERVERSPI_H


class TcpServerSpi {
    virtual void onAccept() = 0;
    virtual void onData(void *msgData, int len) = 0;
    virtual void onDisConnected() = 0;
};


#endif //REACTORSERVER_TCPSERVERSPI_H
