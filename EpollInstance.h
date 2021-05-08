//
// Created by anton on 5/1/21.
//

#ifndef SERVER_C_EPOLLINSTANCE_H
#define SERVER_C_EPOLLINSTANCE_H

#include <unistd.h>    // for close()
#include <sys/epoll.h> // for epoll_create1()
#include <string.h>

#include "EpollFdStruct.h"


#define MAX_EPOLL_EVENTS 30

class EpollFdStruct;

class EpollInstance {
    struct epoll_event event;
    int fd;

public:
    EpollInstance();
    ~EpollInstance();
    void close_fd();

    void registerFD(EpollFdStruct &fd);
    void unregisterFD(EpollFdStruct &fd);
    void waitEvents();
};


#endif //SERVER_C_EPOLLINSTANCE_H
