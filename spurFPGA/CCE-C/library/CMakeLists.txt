cmake_minimum_required(VERSION 3.0)

project(CCE-C)

add_library(CCE-C src/call_rcond.c src/rt_nonfinite.c src/rtGetInf.c src/rtGetNaN.c src/svd.c src/xaxpy.c src/xdotc.c src/xnrm2.c src/xrot.c src/xrotg.c src/xswap.c src/loop_uhat_sparse.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include
                                            "C:/Xilinx/Vitis_HLS/2023.2/include")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -mavx")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg -mavx")
