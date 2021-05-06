//
// Created by anton on 5/6/21.
//

#ifndef SERVER_C_READDATAEVENT_H
#define SERVER_C_READDATAEVENT_H

#include <sys/epoll.h>
#include "EpollFdStruct.h"
#include "EpollInstance.h"

#include <string.h>

// TCP include
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>

#include <cstring>
#include <unistd.h>
#include <byteswap.h>

class ReadDataEvent : public EpollFdStruct {
public:
    ReadDataEvent(uint32_t cfd, EpollInstance &e);
    ~ReadDataEvent();
    void handleEvent(uint32_t events);

protected:
#define SIZE_OF_SIZE_MESSAGE 4
};


#endif //SERVER_C_READDATAEVENT_H
