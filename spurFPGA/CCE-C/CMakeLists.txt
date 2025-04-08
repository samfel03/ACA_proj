cmake_minimum_required(VERSION 3.0)

project(CCE-C_MAIN)

add_subdirectory(library)
add_subdirectory(apps)

#include_directories(/Eigen)

#target_compile_options(main PRIVATE "-Wl, --heap,50000000")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg -mavx")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g -pg -mavx")