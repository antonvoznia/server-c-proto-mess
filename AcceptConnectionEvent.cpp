//
// Created by anton on 5/6/21.
//

#include "AcceptConnectionEvent.h"

#include <iostream>
#include <cstring>

AcceptConnectionEvent::AcceptConnectionEvent(EpollInstance &e, int short port) : EpollFdStruct(-1, e), port(port) {
    this->fd = socket(AF_INET, SOCK_STREAM, 0);

    this->total_words = new dictionary_t;

    std::memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family      = AF_INET;              // IPv4
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);    // Bind to all available interfaces
    saddr.sin_port        = htons(port);          // Requested port

    bind(this->fd, (struct sockaddr *) &saddr, sizeof(saddr));

    int flags = fcntl(this->fd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(this->fd, F_SETFL, flags);

    listen(this->fd, SOMAXCONN);
    registerFd();
    for (int i = 0; i < THREAD_COUNT; i++) {
        thread_pool[i] = std::thread(&AcceptConnectionEvent::waitEvents, this, i);
    }
}

// TODO destructor
AcceptConnectionEvent::~AcceptConnectionEvent() {

}

// per one thread
void AcceptConnectionEvent::waitEvents(int thread_id) {
    std::cout << thread_id << std::endl;
    ep[thread_id].waitEvents();
}

void AcceptConnectionEvent::handleEvent(uint32_t events) {
    if((events & EPOLLERR) || (events & EPOLLHUP) || !(events & EPOLLIN)) {
        std::cout << "Close socket?" << std::endl;
        unregisterFd();
        close(this->fd);
    } else {
        new ReadDataEvent(accept(fd, NULL, NULL), this->ep[next_thread], this->total_words);

        next_thread++;
        if (next_thread == THREAD_COUNT) {
            next_thread = 0;
        }
    }
}

