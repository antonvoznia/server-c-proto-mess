//
// Created by anton on 5/6/21.
//

#include "ReadDataEvent.h"

#include <iostream>

ReadDataEvent::ReadDataEvent(uint32_t cfd, EpollInstance &e) : EpollFdStruct(cfd, e) {
    registerFd();
}

// TODO destructor
ReadDataEvent::~ReadDataEvent() {
}

void ReadDataEvent::handleEvent(uint32_t events) {
    if((events & EPOLLERR) || (events & EPOLLHUP) || !(events & EPOLLIN)){
        unregisterFd();
        close(fd);
        delete this;
    } else{
        Request request;
        Response response;
        char* buff;
        unsigned int size;
        char *data = (char*)&size;
        int left = sizeof(size);
        int count = read(this->fd, data, left);

        if (count < 1) {
            unregisterFd();
            return;
        }
        data += count;
        left -= count;
        std::cout << ntohl(size) << std::endl;
        std::cout << size << std::endl;
        buff = new char [size];
        count = read(this->fd, buff, size);

        if (!request.ParseFromArray((void *) buff, size)) {
            std::cerr << "Failed to parse data!" << std::endl;
            throw "Data were not parsed!\n";
        }

        switch (request.msg_case()) {
            case Request::kGetCount:
                break;
            case Request::kPostWords:
                break;
            default:
                response.set_status(::Response_Status_ERROR);
                response.set_errmsg("Incorrect message case!");
        }
        response.SerializeToFileDescriptor(this->fd);
        delete buff;
    }
}


