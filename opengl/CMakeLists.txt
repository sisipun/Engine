cmake_minimum_required(VERSION 3.14)
project(OpenGL)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(GLM REQUIRED)
find_package(ASSIMP REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${GLM_INCLUDE_DIR} ${assimp_INCLUDE_DIRS})

add_subdirectory(glad/)
add_subdirectory(stbimage/)

set(SOURCE_LIB
    shader.h
    shader.cpp

    camera.h
    camera.cpp

    mesh.h
    mesh.cpp

    model.h
    model.cpp
)

add_library(Components STATIC ${SOURCE_LIB})
add_executable(OpenGL main.cpp)

target_link_libraries(Components GLAD STBIMAGE ${assimp_LIBRARIES} ${GLM_LIBRARIES})
target_link_libraries(OpenGL Components ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})