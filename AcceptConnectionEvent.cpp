//
// Created by anton on 5/6/21.
//

#include "AcceptConnectionEvent.h"
#include "ReadDataEvent.h"

#include <iostream>
#include <cstring>

AcceptConnectionEvent::AcceptConnectionEvent(EpollInstance &e, int short port) : EpollFdStruct(-1, e), port(port) {
    this->fd = socket(AF_INET, SOCK_STREAM, 0);

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

    this->ep = &e;
}

// TODO destructor
AcceptConnectionEvent::~AcceptConnectionEvent() {

}

void AcceptConnectionEvent::handleEvent(uint32_t events) {
    if((events & EPOLLERR) || (events & EPOLLHUP) || !(events & EPOLLIN)) {
        std::cout << "Close socket?" << std::endl;
        unregisterFd();
        close(this->fd);
    } else {
        new ReadDataEvent(accept(fd, NULL, NULL), *this->ep);
    }
}

