cmake_minimum_required(VERSION 3.10)
project(XenTorch LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Try to find CUDA (optional)
find_package(CUDAToolkit QUIET)

if(CUDAToolkit_FOUND)
    message(STATUS "CUDA found! Building with GPU support")
    enable_language(CUDA)
    set(CMAKE_CUDA_ARCHITECTURES "75")
    set(CUDA_SOURCES src/cuda.cu)
else()
    message(STATUS "CUDA not found. Building CPU-only version")
    set(CUDA_SOURCES)
endif()

include_directories(header)

add_library(xentorch STATIC src/source.cpp ${CUDA_SOURCES})

if(CUDAToolkit_FOUND)
    target_link_libraries(xentorch CUDA::cudart)
endif()
