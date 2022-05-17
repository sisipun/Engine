cmake_minimum_required(VERSION 3.14)
project(PickleRenderer)
set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
add_subdirectory(lib/glad/)

add_library(PickleRenderer STATIC 
    include/pickle/renderer.h
    include/pickle/directx_renderer.h src/directx_renderer.cpp
    include/pickle/opengl_renderer.h src/opengl_renderer.cpp
)

target_include_directories(PickleRenderer PUBLIC include)
target_link_libraries(PickleRenderer GLAD ${SDL2_LIBRARIES})