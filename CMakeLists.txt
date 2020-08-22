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
    src/engine/utils/logger/logger.h
    src/engine/utils/logger/logger.cpp
    
    src/engine/utils/time/timer.h
    src/engine/utils/time/timer.cpp

    src/engine/utils/random/random_generator.h

    src/engine/utils/procedural_generation/map.h
    src/engine/utils/procedural_generation/chess_generator.h
    src/engine/utils/procedural_generation/chess_generator.cpp
    src/engine/utils/procedural_generation/drunkard_walk_generator.h
    src/engine/utils/procedural_generation/drunkard_walk_generator.cpp
    src/engine/utils/procedural_generation/cellular_automata_generator.h
    src/engine/utils/procedural_generation/cellular_automata_generator.cpp
    src/engine/utils/procedural_generation/bsp_generator.h
    src/engine/utils/procedural_generation/bsp_generator.cpp
    src/engine/utils/procedural_generation/box_generator.h
    src/engine/utils/procedural_generation/box_generator.cpp

    src/engine/physics/body.h
    src/engine/physics/rigid_body.h

    src/engine/physics/collision.h
    src/engine/physics/collision.cpp

    src/engine/physics/collision_manager.h
    src/engine/physics/collision_manager.cpp

    src/engine/event/event.h

    src/engine/event/event_manager.h
    src/engine/event/event_manager.cpp

    src/engine/actor/actor.h
    src/engine/actor/actor.cpp

    src/engine/actor/scene/scene.h

    src/engine/storage/storage.h
    src/engine/storage/storage.cpp

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

    src/engine/context/context.h
    src/engine/context/context.cpp

    src/engine/engine.h
    src/engine/engine.cpp

    src/utils/constants.h

    src/actor/hero.h
    src/actor/hero.cpp
    
    src/actor/wall.h
    
    src/actor/door.h

    src/actor/mini_map.h
    src/actor/mini_map.cpp
)

add_library(Components STATIC ${SOURCE_LIB})
add_executable(Roguelike ${SOURCE_EXE})

target_link_libraries(Components ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})
target_link_libraries(Roguelike Components)