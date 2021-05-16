//
// Created by anton on 5/6/21.
//

#ifndef SERVER_C_ACCEPTCONNECTIONEVENT_H
#define SERVER_C_ACCEPTCONNECTIONEVENT_H

//
#include <sys/epoll.h>
#include "EpollFdStruct.h"
#include "EpollInstance.h"
#include "ReadDataEvent.h"
#include <thread>
#include <tbb/concurrent_unordered_set.h>

// TCP include
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>

#define THREAD_COUNT 16

class AcceptConnectionEvent : public EpollFdStruct {
public:
    AcceptConnectionEvent(EpollInstance &e, short int port);
    ~AcceptConnectionEvent();

    void handleEvent(uint32_t events);
    void waitEvents(int thread_id);

protected:
    short int port = -1;
    struct sockaddr_in saddr;
    EpollInstance ep[THREAD_COUNT];
    int next_thread = 0;

    std::thread thread_pool[THREAD_COUNT];
    dictionary_t *total_words;
};


#endif //SERVER_C_ACCEPTCONNECTIONEVENT_H
