cmake_minimum_required(VERSION 3.14)
project(PickleRenderer)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(api modules/api)
add_subdirectory(directx modules/directx)
add_subdirectory(metal modules/metal)
add_subdirectory(opengl modules/opengl)

add_library(PickleRenderer INTERFACE)

target_link_libraries(PickleRenderer INTERFACE PickleRendererDirectX PickleRendererOpenGL PickleRendererMetal PickleRendererApi)