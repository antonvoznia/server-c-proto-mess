//
// Created by anton on 5/1/21.
//

#include "EpollInstance.h"

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

void EpollInstance::registerFD(int fd) {
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = fd;

    if(epoll_ctl(this->fd, EPOLL_CTL_ADD, fd, &event)) {
        close_fd();
        throw "Failed to add file descriptor to epoll\n";
    }
}

void EpollInstance::unregisterFD(int fd) {
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = fd;

    if(epoll_ctl(this->fd, EPOLL_CTL_DEL, fd, &event)) {
        close_fd();
        throw "Failed to delete file descriptor to epoll\n";
    }
}