cmake_minimum_required(VERSION 3.14)
project(PickleMathExecutable)
set(CMAKE_CXX_STANDARD 20)

add_library(PickleMath STATIC include/picklemath/math_engine.h src/math_engine.cpp)
add_executable(PickleMathExecutable main.cpp)

target_include_directories(PickleMath PUBLIC include)
target_link_libraries(PickleMathExecutable PickleMath)