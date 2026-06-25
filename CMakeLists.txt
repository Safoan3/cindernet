cmake_minimum_required(VERSION 3.10)
project(XenTorchTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ===== ADD THIS SECTION =====
# Set optimization flags for Release build
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -mtune=native -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")  # Keep debug for development

# Set Release as default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()
# ============================


add_subdirectory(slib/xentorch  ${CMAKE_BINARY_DIR}/slib/xentorch)


include_directories(header)

add_executable(XenTorchTest src/neuralnet.cpp src/test.cpp)
target_link_libraries(XenTorchTest PRIVATE xentorch)  # Or whatever the library target is named

