cmake_minimum_required(VERSION 3.14)
project(Architector)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCE_EXE src/main.cpp)
set(SOURCE_LIB src/components/architector.h src/components/architector.cpp)

add_library(Components STATIC ${SOURCE_LIB})
add_executable(Architector ${SOURCE_EXE})

target_link_libraries(Components ${SDL2_LIBRARIES})
target_link_libraries(Architector Components)