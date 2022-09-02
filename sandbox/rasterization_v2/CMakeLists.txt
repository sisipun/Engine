cmake_minimum_required(VERSION 3.14)
project(Rasterization)
set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_subdirectory(../../math ./build)

add_library(Rasterization STATIC
    include/rasterization/model.h
    include/rasterization/model_instance.h
    include/rasterization/renderer.h src/renderer.cpp
)
add_executable(RasterizationTest main.cpp)

target_include_directories(Rasterization PUBLIC include)
target_link_libraries(Rasterization PickleMath ${SDL2_LIBRARIES})
target_link_libraries(RasterizationTest Rasterization)