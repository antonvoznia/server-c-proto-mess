//
// Created by anton on 5/6/21.
//

#include "ReadDataEvent.h"

#include <iostream>
#include <sstream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>

ReadDataEvent::ReadDataEvent(uint32_t cfd, EpollInstance &e, dictionary_t *total_words) : EpollFdStruct(cfd, e) {
    this->total_words = total_words;
    registerFd();
}

// TODO destructor
ReadDataEvent::~ReadDataEvent() {
}

void ReadDataEvent::addWords(const std::string& data) {

    namespace bio = boost::iostreams;

    std::stringstream compressed(data);
    std::stringstream decompressed;

    bio::filtering_streambuf<bio::input> out;
    out.push(bio::gzip_decompressor());
    out.push(compressed);
    bio::copy(out, decompressed);

    std::string str = decompressed.str();
    std::istringstream iss(str);
    std::string word;

    while (iss >> word) {
        this->total_words->insert(word);
    }
}

void ReadDataEvent::handleEvent(uint32_t events) {

    if((events & EPOLLRDHUP) || (events & EPOLLHUP) || !(events & EPOLLIN)){
        unregisterFd();
        close(fd);
        delete this;
    } else{
        Request request;
        Response response;
        char* buff;
        char* buff_response;
        unsigned int size;
        int rtn = 0;

        char *data = (char*)&size;
        int left = sizeof(size);

        int count = read(this->fd, data, left);

        if (count < 1) {
            unregisterFd();
            return;
        }
        data += count;
        left -= count;
        size = ntohl(size);
        buff = new char [size];
//        count = read(this->fd, buff, size);
        std::vector<char> full_data(size);

        int count_read = 0;
        do {
            int rc = read(this->fd, buff, size);
            full_data.insert(full_data.begin() + count_read, buff, buff + rc);
            count_read += rc;
        } while(count_read != size);

        if (!request.ParseFromArray((void *) full_data.data(), size)) {
            std::cerr << "Failed to parse data!" << std::endl;
            throw "Data were not parsed!\n";
        }

        switch (request.msg_case()) {
            case Request::kGetCount:
                response.set_counter(this->total_words->size());
                response.set_status(Response_Status_OK);
                break;
            case Request::kPostWords:
                addWords(request.postwords().data());
                response.set_status(Response_Status_OK);
                break;
            default:
                response.set_status(Response_Status_ERROR);
                response.set_errmsg("Incorrect message case!");
                break;
        }

        unsigned int size_response = response.ByteSizeLong();
        buff_response = new char[size_response];
        response.SerializePartialToArray(buff_response, size_response);
        unsigned int revert_bits_size = ntohl(size_response);
        data = (char *) &revert_bits_size;

        rtn = write(this->fd, data, sizeof (unsigned int));
        if (rtn != sizeof (unsigned int)) {
            throw "Problem to send size of message!\n";
        }

        rtn = write(this->fd, buff_response, size_response);
        if (rtn != size_response) {
            throw "Problem to send message!\n";
        }
        delete buff_response, buff;
    }
}


