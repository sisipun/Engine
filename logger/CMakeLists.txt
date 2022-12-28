cmake_minimum_required(VERSION 3.14)
if(TARGET PickleLogger)
    return()
endif()

project(PickleLogger)
set(CMAKE_CXX_STANDARD 20)

add_library(PickleLogger STATIC 
    include/pickle/text_modifier.h
    include/pickle/logger.h src/logger.cpp
)
add_executable(PickleLoggerTests tests/tests.cpp)

target_include_directories(PickleLogger PUBLIC include)
target_link_libraries(PickleLoggerTests PickleLogger)