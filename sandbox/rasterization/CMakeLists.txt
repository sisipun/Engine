cmake_minimum_required(VERSION 3.14)
project(Rasterization)
set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_subdirectory(../../math ./build)

add_executable(RasterizationTest main.cpp)

target_link_libraries(RasterizationTest PickleMath ${SDL2_LIBRARIES})