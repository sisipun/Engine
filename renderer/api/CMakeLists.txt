cmake_minimum_required(VERSION 3.14)
if(TARGET PickleRendererApi)
    return()
endif()

project(PickleRendererApi)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/stbimage/)
add_subdirectory(lib/assimp/)

add_library(PickleRendererApi STATIC 
    include/pickle/renderer.h src/renderer.cpp
    include/pickle/camera.h src/camera.cpp
    include/pickle/light/light.h src/light/light.cpp
    include/pickle/light/direct_light.h src/light/direct_light.cpp
    include/pickle/light/point_light.h src/light/point_light.cpp
    include/pickle/model/mesh.h src/model/mesh.cpp
    include/pickle/model/model.h src/model/model.cpp
    include/pickle/model/file_model.h src/model/file_model.cpp
    include/pickle/scene.h src/scene.cpp
    include/pickle/texture.h src/texture.cpp
    include/pickle/shader.h src/shader.cpp
)

target_include_directories(PickleRendererApi PUBLIC include)
target_link_libraries(PickleRendererApi PickleLogger PickleMath StbImage assimp)

set_target_properties(
    assimp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
) 