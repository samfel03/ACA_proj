############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project sparsefpgaimp
set_top loop_uhat_sparse
add_files ../CCE-C/library/src/call_rcond.c
add_files sparsefpgaimp/loop_uhat_sparse.cpp
add_files ../CCE-C/library/src/rtGetInf.c
add_files ../CCE-C/library/src/rtGetNaN.c
add_files ../CCE-C/library/src/rt_nonfinite.c
add_files ../CCE-C/library/src/svd.c
add_files ../CCE-C/library/src/xaxpy.c
add_files ../CCE-C/library/src/xdotc.c
add_files ../CCE-C/library/src/xnrm2.c
add_files ../CCE-C/library/src/xrot.c
add_files ../CCE-C/library/src/xrotg.c
add_files ../CCE-C/library/src/xswap.c
add_files -tb ../CCE-C/library/mainsparse.cpp -cflags "-IC:/Research/CU-Spur-Sean/spurFPGA/CCE-C/library/include -IC:/Research/CU-Spur-Sean/spurFPGA/CCE-C/library/include -Wno-unknown-pragmas"
open_solution "loop_uhat_sparse_imp" -flow_target vivado
set_part {xc7z007s-clg400-1}
create_clock -period 10 -name default
config_export -description {First iteration of AXI Stream Implementation} -flow syn -format ip_catalog -output C:/Research/CU-Spur-Sean/spurFPGA/ExportedVivadoIPZynq/Zynq2.0 -rtl verilog -version 2.0 -vivado_clock 10
config_cosim -tool xsim
source "./sparsefpgaimp/loop_uhat_sparse_imp/directives.tcl"
csim_design -clean
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog -output C:/Research/CU-Spur-Sean/spurFPGA/ExportedVivadoIPZynq/Zynq2.0
