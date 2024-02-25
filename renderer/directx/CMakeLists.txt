cmake_minimum_required(VERSION 3.14)
if(TARGET PickleRendererDirectX)
    return()
endif()

project(PickleRendererDirectX)
set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

find_package(DirectX11 REQUIRED)

add_library(PickleRendererDirectX STATIC 
    include/pickle/directx_renderer.h src/directx_renderer.cpp
)

target_include_directories(PickleRendererDirectX PUBLIC include ${DirectX11_INCLUDE_DIRS})
target_link_libraries(PickleRendererDirectX PickleRendererApi PickleLogger PickleMath ${DirectX11_LIBRARIES})

file(COPY "${PROJECT_SOURCE_DIR}/resource" DESTINATION ${CMAKE_BINARY_DIR})