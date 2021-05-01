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
        throw "Failed to close epoll file descriptor\\n\"";
    }

    this->fd = -1;
}