cmake_minimum_required(VERSION 3.14)
project(Renderer)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

set(SOURCE_LIB
    model.cpp
)

add_library(Components STATIC ${SOURCE_LIB})

add_executable(Renderer main.cpp)

target_link_libraries(Renderer ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} Components)