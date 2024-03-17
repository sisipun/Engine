cmake_minimum_required(VERSION 3.14)
project(PickleRenderer)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(api modules/api)
add_subdirectory(metal modules/metal)
add_subdirectory(opengl modules/opengl)
if(WIN32)
    add_subdirectory(directx modules/directx)
endif()

add_library(PickleRenderer INTERFACE)

target_link_libraries(PickleRenderer INTERFACE PickleRendererApi)
target_link_libraries(PickleRenderer INTERFACE PickleRendererOpenGL)
target_link_libraries(PickleRenderer INTERFACE PickleRendererMetal)
if(WIN32)
    target_link_libraries(PickleRenderer INTERFACE PickleRendererDirectX)
endif()