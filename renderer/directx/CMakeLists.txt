cmake_minimum_required(VERSION 3.14)
if(TARGET PickleRendererDirectX)
    return()
endif()

project(PickleRendererDirectX)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(../api ./apiBuild)
add_subdirectory(../../logger ./loggerBuild)

add_library(PickleRendererDirectX STATIC 
    include/pickle/directx_renderer.h src/directx_renderer.cpp
)

target_include_directories(PickleRendererDirectX PUBLIC include)
target_link_libraries(PickleRendererDirectX PickleRendererApi PickleLogger)