//
// Created by anton on 5/1/21.
//

#include "EpollInstance.h"
#include <iostream>

EpollInstance::EpollInstance() {
    this->fd = epoll_create1(0);

    if (this->fd == -1) {
        throw "Failed to create epoll file descriptor\n";
    }
}

EpollInstance::~EpollInstance() {
    if (this->fd != -1) {
        close_fd();
    }
}

void EpollInstance::close_fd() {
    if (close(this->fd)) {
        throw "Failed to close epoll file descriptor\n";
    }

    this->fd = -1;
}

void EpollInstance::registerFD(EpollFdStruct &efd) {
    struct epoll_event event;
    memset(&event,0,sizeof(event));

    event.events = EPOLLIN;
    event.data.ptr = &efd;

    if(epoll_ctl(this->fd, EPOLL_CTL_ADD, efd.fd, &event)) {
        close_fd();
        throw "Failed to add file descriptor to epoll\n";
    }
}

void EpollInstance::unregisterFD(EpollFdStruct &efd) {
    struct epoll_event event;
    memset(&event,0,sizeof(event));

    event.events = 0;
    event.data.ptr = &efd;

    if(epoll_ctl(this->fd, EPOLL_CTL_DEL, efd.fd, &event)) {
        close_fd();
        throw "Failed to delete file descriptor to epoll\n";
    }
}

void EpollInstance::waitEvents() {
    struct epoll_event events[MAX_EPOLL_EVENTS];
    while(true) {
        int eventCount = epoll_wait(this->fd, events, MAX_EPOLL_EVENTS, -1);

        if (eventCount == -1) {
            throw "Error: cannot get event count!\n";
        }

        for (int i = 0; i < eventCount; i++) {
            // TODO to process the events
            static_cast<EpollFdStruct*>(events[i].data.ptr)->handleEvent(events[i].events);
        }
    }
}