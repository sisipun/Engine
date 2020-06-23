cmake_minimum_required(VERSION 3.14)
project(MultiGame)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCE_EXE src/main.cpp)
set(SOURCE_LIB 
    src/components/socket/socket_address.h
    src/components/socket/socket_address.cpp

    src/components/socket/socket_address_factory.h 

    src/components/socket/tcp_socket.h
    src/components/socket/tcp_socket.cpp

    src/components/socket/udp_socket.h
    src/components/socket/udp_socket.cpp
    
    src/components/socket/socket_utils.h

    src/components/stream/input_memory_stream.h
    src/components/stream/input_memory_stream.cpp
    src/components/stream/output_memory_stream.h
    src/components/stream/output_memory_stream.cpp
)

add_library(Components STATIC ${SOURCE_LIB})
add_executable(MultiGame ${SOURCE_EXE})

target_link_libraries(Components ${SDL2_LIBRARIES})
target_link_libraries(MultiGame Components)