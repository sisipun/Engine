cmake_minimum_required(VERSION 3.14)
project(Raytracing)
set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_subdirectory(../../math ./build)

add_library(Raytracing STATIC   
    include/raytracing/color.h
    include/raytracing/shape.h
    include/raytracing/sphere.h src/sphere.cpp
    include/raytracing/light.h
    include/raytracing/point_light.h
    include/raytracing/direct_light.h
    include/raytracing/ambient_light.h
    include/raytracing/renderer.h src/renderer.cpp
)
add_executable(RaytracingTest main.cpp)

target_include_directories(Raytracing PUBLIC include)
target_link_libraries(Raytracing PickleMath ${SDL2_LIBRARIES})
target_link_libraries(RaytracingTest Raytracing)