# Find the DirectX11 includes and library
# This module defines
#  DirectX11_INCLUDE_DIRS, where to find d3d11.h, etc.
#  DirectX11_ROOT_DIR, directory where DirectX11 was installed.
#  DirectX11_LIBRARIES, libraries to link against to use DirectX11.
#  DirectX11_FOUND, If false, do not try to use DirectX11.

find_path(DirectX11_INCLUDE_DIRS d3d11.h PATHS "$ENV{DXSDK_DIR}/Include" "$ENV{PROGRAMFILES}/Microsoft DirectX SDK*/Include")

get_filename_component(DirectX11_ROOT_DIR "${DirectX11_INCLUDE_DIRS}/.." ABSOLUTE)

if(CMAKE_CL_64)
  set(DirectX11_LIBPATH_SUFFIX "x64")
else()
  set(DirectX11_LIBPATH_SUFFIX "x86")
endif()

find_library(DirectX11_D3D11_LIBRARY d3d11 HINTS "${DirectX11_ROOT_DIR}/Lib/" PATH_SUFFIXES ${DirectX11_LIBPATH_SUFFIX} NO_DEFAULT_PATH)
find_library(DirectX11_D3DX11_LIBRARY d3dx11 HINTS "${DirectX11_ROOT_DIR}/Lib/" PATH_SUFFIXES ${DirectX11_LIBPATH_SUFFIX} NO_DEFAULT_PATH)
set(DirectX11_LIBRARIES ${DirectX11_D3D11_LIBRARY} ${DirectX11_D3DX11_LIBRARY})

# handle the QUIETLY and REQUIRED arguments and set DirectX11_FOUND to TRUE if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(DirectX11 DEFAULT_MSG DirectX11_INCLUDE_DIRS DirectX11_ROOT_DIR DirectX11_LIBRARIES)
mark_as_advanced(DirectX11_D3D11_LIBRARY DirectX11_D3DX11_LIBRARY)