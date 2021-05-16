# server-c-proto-mess
Server is written in C++ to process data in Proto Buff and to response the processed data. The server uses epoll mechanism.

### Needed libraries
* Protocol Buffer https://developers.google.com/protocol-buffers/docs/cpptutorial
* TBB https://github.com/oneapi-src/oneTBB

### Compile
```
install all reqired libraries
git clone https://github.com/antonvoznia/server-c-proto-mess.git
cd server-c-proto-mess
protoc --cpp_out=. messages.proto       // generate message class for your system
cmake .
make
./Server_c port
```

### Logic
The server uses epoll to register events like to accept a connection and read data form file descriptor.
Each connection is adding to according thread in round robin algorithm.
In AcceptConnection.h you can set total count of threads.
