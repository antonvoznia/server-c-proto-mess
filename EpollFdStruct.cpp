//
// Created by anton on 5/2/21.
//

#include "EpollFdStruct.h"

EpollFdStruct::EpollFdStruct(int fd, EpollInstance &e) : fd(fd), epollInstance(e) {}

EpollFdStruct::~EpollFdStruct() {}

void EpollFdStruct::unregisterFd() {
    epollInstance.unregisterFD(*this);
}
void EpollFdStruct::registerFd() {
    epollInstance.registerFD(*this);
}