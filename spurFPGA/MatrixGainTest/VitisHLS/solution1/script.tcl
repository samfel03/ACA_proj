############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project VitisHLS
set_top doGain
add_files VitisHLS/core.cpp
add_files -tb VitisHLS/test_core.cpp -cflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xc7z007s-clg400-1}
create_clock -period 10 -name default
config_export -format ip_catalog -output C:/Research/CU-Spur-Sean/spurFPGA/MatrixGainTest/HLSIP -rtl verilog -version 1.0
source "./VitisHLS/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog -output C:/Research/CU-Spur-Sean/spurFPGA/MatrixGainTest/HLSIP
