cmake_minimum_required(VERSION 3.14)
if(TARGET PickleRendererMetal)
    return()
endif()

project(PickleRendererMetal)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(../api ./apiBuild)
add_subdirectory(../../logger ./loggerBuild)

add_library(PickleRendererMetal STATIC 
    include/pickle/metal_renderer.h src/metal_renderer.cpp
)

target_include_directories(PickleRendererMetal PUBLIC include)
target_link_libraries(PickleRendererMetal PickleRendererApi PickleLogger)