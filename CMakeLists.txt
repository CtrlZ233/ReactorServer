cmake_minimum_required(VERSION 3.27)
include_directories(spdlog/include)
project(ReactorServer)

set(CMAKE_CXX_STANDARD 20)

add_executable(ReactorServer main.cpp
        Connection.cpp
        Connection.h
        mpsc.h
        EpollServer.cpp
        EpollServer.h
        TcpServerApi.cpp
        TcpServerApi.h
        TcpServerSpi.h
        PidAllocator.cpp
        PidAllocator.h)
