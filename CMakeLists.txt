cmake_minimum_required(VERSION 3.19)
project(Server_c)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
#add_executable(Server_c main.cpp EpollInstance.cpp EpollFdStruct.cpp AcceptUsersHandle.cpp)

target_link_libraries(Server_c PRIVATE protobuf OpenMP::OpenMP_CXX)