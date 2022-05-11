cmake_minimum_required(VERSION 3.14)
project(PickleRenderer)
set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
add_subdirectory(../math ./build)

add_library(PickleRenderer STATIC 
    include/pickle/color.h
    include/pickle/model.h src/model.cpp
    include/pickle/renderer.h src/renderer.cpp
)
add_executable(PickleRendererTest main.cpp)

target_include_directories(PickleRenderer PUBLIC include)
target_link_libraries(PickleRenderer PickleMath ${SDL2_LIBRARIES})
target_link_libraries(PickleRendererTest PickleRenderer)