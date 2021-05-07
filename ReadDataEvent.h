//
// Created by anton on 5/6/21.
//

#ifndef SERVER_C_READDATAEVENT_H
#define SERVER_C_READDATAEVENT_H

#include <sys/epoll.h>
#include "EpollFdStruct.h"
#include "EpollInstance.h"

#include "messages.pb.h"

#include <string.h>
#include <set>

// TCP include
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>

#include <byteswap.h>

typedef std::set<std::string> dictionary_t;

class ReadDataEvent : public EpollFdStruct {
public:
    ReadDataEvent(uint32_t cfd, EpollInstance &e, dictionary_t *total_words);
    ~ReadDataEvent();
    void handleEvent(uint32_t events);

protected:
    dictionary_t *total_words;
};


#endif //SERVER_C_READDATAEVENT_H
