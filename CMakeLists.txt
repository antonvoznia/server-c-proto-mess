cmake_minimum_required(VERSION 3.19)
project(Server_c)

set(CMAKE_CXX_STANDARD 17)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(Server_c PRIVATE boost_iostreams tbb PRIVATE ${TBB_IMPORTED_TARGETS} Threads::Threads protobuf ${Boost_LIBRARIES})