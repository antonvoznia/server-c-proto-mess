//
// Created by anton on 5/1/21.
//

#ifndef SERVER_C_EPOLLINSTANCE_H
#define SERVER_C_EPOLLINSTANCE_H

#include <unistd.h>    // for close()
#include <sys/epoll.h> // for epoll_create1()
#include <string.h>


#define MAX_EPOLL_EVENTS 100

class EpollInstance {
    struct epoll_event event;
    int fd;

public:
    EpollInstance();
    ~EpollInstance();
    void close_fd();

    void registerFD(int fd);
    void unregisterFD(int fd);
    void waitEvents();
};


#endif //SERVER_C_EPOLLINSTANCE_H
