cmake_minimum_required(VERSION 3.14)
project(PickleRenderer)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(directx directxBuild)
add_subdirectory(metal metalBuild)
add_subdirectory(opengl openglBuild)

add_library(PickleRenderer INTERFACE)

target_link_libraries(PickleRenderer INTERFACE PickleRendererDirectX PickleRendererOpenGL PickleRendererMetal PickleRendererApi)