cmake_minimum_required(VERSION 3.14)
project(PickleRenderer)
set(CMAKE_CXX_STANDARD 20)

add_library(PickleRenderer STATIC include/picklerenderer/renderer.h src/renderer.cpp)

target_include_directories(PickleRenderer PUBLIC include)