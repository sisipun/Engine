cmake_minimum_required(VERSION 3.14)
if(TARGET PickleMath)
    return()
endif()

project(PickleMath)
set(CMAKE_CXX_STANDARD 20)

find_package(Catch2 REQUIRED)

add_library(PickleMath STATIC include/pickle/math.h src/math.cpp)
add_executable(PickleMathTests tests/tests.cpp)

target_include_directories(PickleMath PUBLIC include)
target_link_libraries(PickleMathTests PickleMath Catch2::Catch2WithMain)