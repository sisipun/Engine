cmake_minimum_required(VERSION 3.14)
project(PickleRenderer)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(../math ./build)

add_library(PickleRenderer STATIC 
    include/picklerenderer/renderer.h src/renderer.cpp
    include/picklerenderer/directx_renderer.h src/directx_renderer.cpp
    include/picklerenderer/opengl_renderer.h src/opengl_renderer.cpp
    include/picklerenderer/vulkan_renderer.h src/vulkan_renderer.cpp
    include/picklerenderer/metal_renderer.h src/metal_renderer.cpp
)
add_executable(PickleRendererTest main.cpp)

target_include_directories(PickleRenderer PUBLIC include)
target_link_libraries(PickleRenderer PickleMath)
target_link_libraries(PickleRendererTest PickleRenderer)