cmake_minimum_required(VERSION 3.14)
project(Animation)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(GLM REQUIRED)
find_package(ASSIMP REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${GLM_INCLUDE_DIR} ${assimp_INCLUDE_DIRS})

add_subdirectory(../../math ./mathBuild)
add_subdirectory(lib/glad/)
add_subdirectory(lib/stbimage/)

add_executable(Animation main.cpp)

target_link_libraries(Animation PickleMath GLAD STBIMAGE ${assimp_LIBRARIES} ${GLM_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})