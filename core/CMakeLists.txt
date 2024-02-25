cmake_minimum_required(VERSION 3.14)
project(PickleCore)
set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
add_subdirectory(../math ./mathBuild)
add_subdirectory(../logger ./loggerBuild)
add_subdirectory(../renderer ./rendererBuild)

add_library(PickleCore STATIC 
    include/pickle/window.h src/window.cpp
    include/pickle/sdl_window.h src/sdl_window.cpp
    include/pickle/win32_window.h src/win32_window.cpp
    include/pickle/application.h src/application.cpp
)
add_executable(PickleCoreTest main.cpp)

target_include_directories(PickleCore PUBLIC include)
target_link_libraries(PickleCore PickleMath PickleLogger PickleRenderer ${SDL2_LIBRARIES})
target_link_libraries(PickleCoreTest PickleCore)

file(COPY "${SDL2_BINDIR}/" DESTINATION ${CMAKE_BINARY_DIR} FILES_MATCHING PATTERN "*.dll")