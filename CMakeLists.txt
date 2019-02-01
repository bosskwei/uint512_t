# Minimal version of CMake
cmake_minimum_required (VERSION 3.7)

# Flags
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_COMPILER /usr/bin/clang++-6.0)

set(CMAKE_BUILD_TYPE Debug)
 
# Define project name
project(uint128_t)

#
include_directories(${OPENCL_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

#
add_library(wrapper SHARED
    src/wrapper.cpp
)

#
add_executable(main src/main.cpp)
# target_link_libraries(main Thread)

