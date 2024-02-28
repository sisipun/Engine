cmake_minimum_required(VERSION 3.14)
if(TARGET PickleRendererOpenGL)
    return()
endif()

project(PickleRendererOpenGL)
set(CMAKE_CXX_STANDARD 20)

add_library(PickleRendererOpenGL STATIC 
    include/pickle/opengl_renderer.h src/opengl_renderer.cpp
)

target_include_directories(PickleRendererOpenGL PUBLIC include)
target_link_libraries(PickleRendererOpenGL PickleRendererApi PickleLogger PickleMath Glad SDL2)

file(COPY "${PROJECT_SOURCE_DIR}/resource" DESTINATION ${CMAKE_BINARY_DIR})