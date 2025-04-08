############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project VitisHLS
set_top add
add_files VitisHLS/add.cpp
add_files -tb VitisHLS/nandtb.cpp -cflags "-IC:/Research/CU-Spur-Sean/spurFPGA/SoCNANDTest/VitisHLS/. -Wno-unknown-pragmas"
add_files -tb VitisHLS/nandtb.h
open_solution "solution_1" -flow_target vivado
set_part {xc7z007s-clg400-1}
create_clock -period 10 -name default
config_cosim -tool xsim
config_export -format ip_catalog -output C:/Research/CU-Spur-Sean/spurFPGA/SoCNANDTest/IP/2.0Adder -rtl verilog -version 2.0
source "./VitisHLS/solution_1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog -output C:/Research/CU-Spur-Sean/spurFPGA/SoCNANDTest/IP/2.0Adder
