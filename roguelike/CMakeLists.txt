cmake_minimum_required(VERSION 3.14)
project(Roguelike)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

set(ENGINE 
    engine/utils/logger/logger.h
    engine/utils/logger/logger.cpp

    engine/utils/time/timer.h
    engine/utils/time/timer.cpp

    engine/utils/random/random_generator.h

    engine/physics/body.h

    engine/physics/collision.h
    engine/physics/collision.cpp

    engine/event/event.h

    engine/event/event_manager.h
    engine/event/event_manager.cpp

    engine/actor/actor.h
    engine/actor/actor.cpp

    engine/storage/storage.h
    engine/storage/storage.cpp

    engine/network/socket/socket_address.h
    engine/network/socket/socket_address.cpp

    engine/network/socket/socket_address_factory.h 

    engine/network/socket/tcp_socket.h
    engine/network/socket/tcp_socket.cpp

    engine/network/socket/udp_socket.h
    engine/network/socket/udp_socket.cpp
    
    engine/network/socket/socket_utils.h

    engine/network/stream/input_memory_stream.h
    engine/network/stream/input_memory_stream.cpp
    engine/network/stream/output_memory_stream.h
    engine/network/stream/output_memory_stream.cpp

    engine/context/context.h
    engine/context/context.cpp

    engine/engine.h
    engine/engine.cpp
)

set(SOURCE_EXE roguelike/main.cpp)
set(SOURCE_LIB
    roguelike/utils/constants.h

    roguelike/utils/procedural_generation/map.h
    roguelike/utils/procedural_generation/drunkard_walk_generator.h
    roguelike/utils/procedural_generation/drunkard_walk_generator.cpp

    roguelike/actor/bullet.h
    roguelike/actor/bullet.cpp

    roguelike/actor/enemy.h
    roguelike/actor/enemy.cpp

    roguelike/actor/hero.h
    roguelike/actor/hero.cpp
    
    roguelike/actor/wall.h
    
    roguelike/actor/door.h
    roguelike/actor/door.cpp

    roguelike/actor/mini_map.h
    roguelike/actor/mini_map.cpp
)

add_library(Enigne STATIC ${ENGINE})
add_library(Components STATIC ${SOURCE_LIB})
add_executable(Roguelike ${SOURCE_EXE})

target_link_libraries(Enigne ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})
target_link_libraries(Components Enigne)
target_link_libraries(Roguelike Components)