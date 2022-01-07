cmake_minimum_required(VERSION 3.14)
project(PickleMath)
set(CMAKE_CXX_STANDARD 20)

find_package(Catch2 REQUIRED)

add_library(PickleMath STATIC include/picklemath/math_engine.h src/math_engine.cpp)
add_executable(PickleMathTests tests/tests.cpp)

target_include_directories(PickleMath PUBLIC include)
target_link_libraries(PickleMathTests PickleMath Catch2::Catch2)