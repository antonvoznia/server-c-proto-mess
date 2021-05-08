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
#include <vector>
#include <limits>
#include <set>

// TCP include
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>

#include <byteswap.h>

#include <tbb/concurrent_unordered_set.h>

typedef tbb::concurrent_unordered_set<std::string> dictionary_t;

class ReadDataEvent : public EpollFdStruct {
public:
    ReadDataEvent(uint32_t cfd, EpollInstance &e, dictionary_t *total_words);
    ~ReadDataEvent();
    void addWords(const std::string& data);
    void handleEvent(uint32_t events);

protected:
    dictionary_t *total_words;
};


#endif //SERVER_C_READDATAEVENT_H
