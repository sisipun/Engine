cmake_minimum_required(VERSION 3.14)
project(Roguelike)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

set(SOURCE_EXE src/main.cpp)
set(SOURCE_LIB
    src/engine/logger/logger.h
    src/engine/logger/logger.cpp
    
    src/engine/time/timer.h
    src/engine/time/timer.cpp

    src/engine/physics/body.h

    src/engine/engine.h
    src/engine/engine.cpp

    src/engine/actor/actor.h
    src/engine/actor/actor.cpp

    src/engine/storage/storage.h
    src/engine/storage/storage.cpp

    src/engine/scene/scene.h

    src/engine/network/socket/socket_address.h
    src/engine/network/socket/socket_address.cpp

    src/engine/network/socket/socket_address_factory.h 

    src/engine/network/socket/tcp_socket.h
    src/engine/network/socket/tcp_socket.cpp

    src/engine/network/socket/udp_socket.h
    src/engine/network/socket/udp_socket.cpp
    
    src/engine/network/socket/socket_utils.h

    src/engine/network/stream/input_memory_stream.h
    src/engine/network/stream/input_memory_stream.cpp
    src/engine/network/stream/output_memory_stream.h
    src/engine/network/stream/output_memory_stream.cpp

    src/utils/constants.h

    src/actor/hero.h
    src/actor/hero.cpp

    src/scene/main_scene.h
    src/scene/main_scene.cpp
)

add_library(Components STATIC ${SOURCE_LIB})
add_executable(Roguelike ${SOURCE_EXE})

target_link_libraries(Components ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})
target_link_libraries(Roguelike Components)