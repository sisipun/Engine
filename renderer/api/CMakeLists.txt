cmake_minimum_required(VERSION 3.14)
if(TARGET PickleRendererApi)
    return()
endif()

project(PickleRendererApi)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(../../math ./mathBuild)

add_library(PickleRendererApi STATIC 
    include/pickle/renderer.h src/renderer.cpp
    include/pickle/camera.h src/camera.cpp
    include/pickle/model.h src/model.cpp
    include/pickle/scene.h src/scene.cpp
    include/pickle/texture.h src/texture.cpp
)

target_include_directories(PickleRendererApi PUBLIC include)
target_link_libraries(PickleRendererApi PickleMath)