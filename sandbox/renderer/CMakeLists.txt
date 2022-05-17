cmake_minimum_required(VERSION 3.14)
project(PickleRenderer)
set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package(GLM REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${GLM_INCLUDE_DIR})
add_subdirectory(../../math ./build)
add_subdirectory(lib/stbimage/)

add_library(PickleRenderer STATIC 
    include/pickle/color.h
    include/pickle/model.h src/model.cpp
    include/pickle/texture.h src/texture.cpp
    include/pickle/renderer.h src/renderer.cpp
)
add_executable(PickleRendererTest main.cpp)

target_include_directories(PickleRenderer PUBLIC include)
target_link_libraries(PickleRenderer PickleMath STBIMAGE ${GLM_LIBRARIES} ${SDL2_LIBRARIES})
target_link_libraries(PickleRendererTest PickleRenderer)