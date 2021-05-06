//
// Created by anton on 5/6/21.
//

#ifndef SERVER_C_ACCEPTCONNECTIONEVENT_H
#define SERVER_C_ACCEPTCONNECTIONEVENT_H

//
#include <sys/epoll.h>
#include "EpollFdStruct.h"
#include "EpollInstance.h"

// TCP include
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>



class AcceptConnectionEvent : public EpollFdStruct {
public:
    AcceptConnectionEvent(EpollInstance &e, short int port);
    ~AcceptConnectionEvent();

    void handleEvent(uint32_t events);

protected:
    short int port = -1;
    struct sockaddr_in saddr;
    EpollInstance *ep;
};


#endif //SERVER_C_ACCEPTCONNECTIONEVENT_H
