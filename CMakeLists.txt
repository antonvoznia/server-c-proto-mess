cmake_minimum_required(VERSION 3.19)
project(Server_c)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)

add_executable(Server_c main.cpp EpollInstance.cpp AcceptUsersHandle.cpp)

target_link_libraries(Server_c PRIVATE OpenMP::OpenMP_CXX)