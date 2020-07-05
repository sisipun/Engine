cmake_minimum_required(VERSION 3.14)
project(Roguelike)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCE_EXE src/main.cpp)
set(SOURCE_LIB
    src/utils/constants.h

    src/engine/time/timer.h
    src/engine/time/timer.cpp

    src/engine/physics/body.h


    src/engine/engine.h
    src/engine/engine.cpp

    src/engine/actor/actor_info.h

    src/engine/actor/actor.h
    src/engine/actor/actor.cpp

    src/engine/controller/controller.h
    src/engine/controller/controller.cpp

    src/controller/user_controller.h
    src/controller/user_controller.cpp

    src/network/socket/socket_address.h
    src/network/socket/socket_address.cpp

    src/network/socket/socket_address_factory.h 

    src/network/socket/tcp_socket.h
    src/network/socket/tcp_socket.cpp

    src/network/socket/udp_socket.h
    src/network/socket/udp_socket.cpp
    
    src/network/socket/socket_utils.h

    src/network/stream/input_memory_stream.h
    src/network/stream/input_memory_stream.cpp
    src/network/stream/output_memory_stream.h
    src/network/stream/output_memory_stream.cpp
)

add_library(Components STATIC ${SOURCE_LIB})
add_executable(Roguelike ${SOURCE_EXE})

target_link_libraries(Components ${SDL2_LIBRARIES})
target_link_libraries(Roguelike Components)