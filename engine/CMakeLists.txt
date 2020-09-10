cmake_minimum_required(VERSION 3.14)
project(Engine)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

set(SOURCE_LIB
    utils/logger/logger.h
    utils/logger/logger.cpp
    
    utils/time/timer.h
    utils/time/timer.cpp

    utils/random/random_generator.h

    physics/body.h

    physics/collision.h
    physics/collision.cpp

    event/event.h

    event/event_manager.h
    event/event_manager.cpp

    actor/actor.h
    actor/actor.cpp

    storage/storage.h
    storage/storage.cpp

    network/socket/socket_address.h
    network/socket/socket_address.cpp

    network/socket/socket_address_factory.h 

    network/socket/tcp_socket.h
    network/socket/tcp_socket.cpp

    network/socket/udp_socket.h
    network/socket/udp_socket.cpp
    
    network/socket/socket_utils.h

    network/stream/input_memory_stream.h
    network/stream/input_memory_stream.cpp
    network/stream/output_memory_stream.h
    network/stream/output_memory_stream.cpp

    context/context.h
    context/context.cpp

    engine.h
    engine.cpp
)

set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(Engine SHARED ${SOURCE_LIB})

target_link_libraries(Engine ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})