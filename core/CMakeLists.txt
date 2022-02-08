cmake_minimum_required(VERSION 3.14)
project(PickleCore)
set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
add_subdirectory(../math ./build)
add_subdirectory(lib/glad/)

add_library(PickleCore STATIC 
    include/pickle/renderer.h
    include/pickle/window.h src/window.cpp
    include/pickle/application.h src/application.cpp
    include/pickle/directx_renderer.h src/directx_renderer.cpp
    include/pickle/opengl_renderer.h src/opengl_renderer.cpp
)
add_executable(PickleCoreTest main.cpp)

target_include_directories(PickleCore PUBLIC include)
target_link_libraries(PickleCore PickleMath GLAD ${SDL2_LIBRARIES})
target_link_libraries(PickleCoreTest PickleCore)