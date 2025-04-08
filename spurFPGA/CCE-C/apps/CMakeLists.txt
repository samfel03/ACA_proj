cmake_minimum_required(VERSION 3.0)

project(main)

add_executable(main mainsparse.cpp)

target_link_libraries(main PRIVATE CCE-C)

#include_directories(${PROJECT_SOURCE_DIR}/eigen-master/)

#target_link_libraries(main PRIVATE CCE-C "-Wl,--heap=50000000")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg -mavx")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g -pg -mavx")