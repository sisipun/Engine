cmake_minimum_required(VERSION 3.14)
if(TARGET PickleRendererApi)
    return()
endif()

project(PickleRendererApi)
set(CMAKE_CXX_STANDARD 20)

add_library(PickleRendererApi STATIC 
    include/pickle/renderer.h src/renderer.cpp
)

target_include_directories(PickleRendererApi PUBLIC include)