//
// Created by anton on 5/1/21.
//

#ifndef SERVER_C_EPOLLINSTANCE_H
#define SERVER_C_EPOLLINSTANCE_H

#include <unistd.h>    // for close()
#include <sys/epoll.h> // for epoll_create1()

class EpollInstance {
    int fd;

public:
    EpollInstance();
    ~EpollInstance();

    void close_fd();
};


#endif //SERVER_C_EPOLLINSTANCE_H
