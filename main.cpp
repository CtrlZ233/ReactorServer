#include <iostream>
#include<stdio.h>
#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<sys/fcntl.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<errno.h>
#include<sys/types.h>
#include <arpa/inet.h>

#include "spdlog/spdlog.h"

int main(int argc, char *argv[]) {
    int listenFd;
    listenFd = socket(AF_INET, SOCK_STREAM, 0);// in socket code,it must be AF_INET(protocol)
    if(listenFd == -1) {
        spdlog::error("socket create fail");
        return -1;
    }
    sockaddr_in serverAddr {};
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(atoi(argv[1]));//specify port

    if (bind(listenFd, (sockaddr *)&serverAddr, sizeof(serverAddr)) != 0) {
        spdlog::error("bind failed \n");
        return -1;
    }
    if (listen(listenFd, 5) != 0) {
        spdlog::error("Listen failed\n");
        close(listenFd);
        return -1;
    }

    int clientFd;
    socklen_t len = 0;
    sockaddr_in remoteAddr {};
    while (true) {
        if ((clientFd = ::accept(listenFd, (sockaddr *)&remoteAddr, &len)) < 0) {
            spdlog::error("accept socket error: %s(errno: %d)", strerror(errno), errno);
            return -1;
        }
    }
}
