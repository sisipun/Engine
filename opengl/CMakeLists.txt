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

add_subdirectory(lib/glad/)
add_subdirectory(lib/stbimage/)

set(SOURCE_LIB
    src/model/shader.h
    src/model/shader.cpp

    src/camera/camera.h
    src/camera/camera.cpp

    src/light/light.h
    src/light/light.cpp

    src/light/point_light.h
    src/light/point_light.cpp

    src/light/dir_light.h
    src/light/dir_light.cpp

    src/model/material.h
    src/model/material.cpp

    src/model/mesh.h
    src/model/mesh.cpp

    src/model/model.h
    src/model/model.cpp

    src/model/file_model.h
    src/model/file_model.cpp

    src/scene/scene.h
    src/scene/scene.cpp
    src/scene/scene_generator.h

    src/renderer.h
    src/renderer.cpp
)

add_library(Components STATIC ${SOURCE_LIB})
add_executable(OpenGL src/main.cpp)

target_link_libraries(Components GLAD STBIMAGE ${assimp_LIBRARIES} ${GLM_LIBRARIES}  ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})
target_link_libraries(OpenGL Components)