//
// Created by anton on 5/2/21.
//

#ifndef SERVER_C_EPOLLFDSTRUCT_H
#define SERVER_C_EPOLLFDSTRUCT_H

#include <stdint.h>

#include "EpollInstance.h"

class EpollInstance;

class EpollFdStruct {

public:
    virtual void handleEvent(uint32_t events) = 0;

    EpollFdStruct(int fd, EpollInstance &e);
    virtual ~EpollFdStruct();

    void unregisterFd();
    void registerFd();

protected:
    int fd;
    EpollInstance &epollInstance;

    friend class EpollInstance;
};


#endif //SERVER_C_EPOLLFDSTRUCT_H
