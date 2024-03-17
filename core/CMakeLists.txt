cmake_minimum_required(VERSION 3.14)
project(PickleCore)
set(CMAKE_CXX_STANDARD 20)

# External libs
add_subdirectory(../lib/stbimage/ modules/lib/stbimage)
add_subdirectory(../lib/glad/ modules/lib/glad)
add_subdirectory(../lib/assimp/ modules/lib/assimp)
add_subdirectory(../lib/SDL/ modules/lib/sdl)

set_target_properties(assimp PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set_target_properties(SDL2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Pickle modules
add_subdirectory(../math modules/math)
add_subdirectory(../logger modules/logger)
add_subdirectory(../renderer modules/renderer)

add_library(PickleCore STATIC 
    include/pickle/window.h src/window.cpp
    include/pickle/sdl_window.h src/sdl_window.cpp
    include/pickle/application.h src/application.cpp
)
if (WIN32)
    target_sources(PickleCore PRIVATE include/pickle/win32_window.h src/win32_window.cpp)
endif()
add_executable(PickleCoreTest main.cpp)

target_include_directories(PickleCore PUBLIC include)
target_link_libraries(PickleCore PickleMath PickleLogger PickleRenderer SDL2)
target_link_libraries(PickleCoreTest PickleCore)