// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2023.2 (win64) Build 4029153 Fri Oct 13 20:14:34 MDT 2023
// Date        : Fri Aug  2 15:10:59 2024
// Host        : gerard running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/Research/CU-Spur-Sean/spurFPGA/VitisHLS/sparsefpgaimp/loop_uhat_sparse_imp/impl/verilog/project.gen/sources_1/bd/bd_0/ip/bd_0_hls_inst_0/bd_0_hls_inst_0_stub.v
// Design      : bd_0_hls_inst_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z007sclg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "loop_uhat_sparse,Vivado 2023.2" *)
module bd_0_hls_inst_0(s_axi_CTRL_BUS_AWADDR, 
  s_axi_CTRL_BUS_AWVALID, s_axi_CTRL_BUS_AWREADY, s_axi_CTRL_BUS_WDATA, 
  s_axi_CTRL_BUS_WSTRB, s_axi_CTRL_BUS_WVALID, s_axi_CTRL_BUS_WREADY, 
  s_axi_CTRL_BUS_BRESP, s_axi_CTRL_BUS_BVALID, s_axi_CTRL_BUS_BREADY, 
  s_axi_CTRL_BUS_ARADDR, s_axi_CTRL_BUS_ARVALID, s_axi_CTRL_BUS_ARREADY, 
  s_axi_CTRL_BUS_RDATA, s_axi_CTRL_BUS_RRESP, s_axi_CTRL_BUS_RVALID, 
  s_axi_CTRL_BUS_RREADY, ap_clk, ap_rst_n, interrupt, inStream_TVALID, inStream_TREADY, 
  inStream_TDATA, inStream_TLAST, inStream_TKEEP, inStream_TSTRB, outStream_TVALID, 
  outStream_TREADY, outStream_TDATA, outStream_TLAST, outStream_TKEEP, outStream_TSTRB)
/* synthesis syn_black_box black_box_pad_pin="s_axi_CTRL_BUS_AWADDR[5:0],s_axi_CTRL_BUS_AWVALID,s_axi_CTRL_BUS_AWREADY,s_axi_CTRL_BUS_WDATA[31:0],s_axi_CTRL_BUS_WSTRB[3:0],s_axi_CTRL_BUS_WVALID,s_axi_CTRL_BUS_WREADY,s_axi_CTRL_BUS_BRESP[1:0],s_axi_CTRL_BUS_BVALID,s_axi_CTRL_BUS_BREADY,s_axi_CTRL_BUS_ARADDR[5:0],s_axi_CTRL_BUS_ARVALID,s_axi_CTRL_BUS_ARREADY,s_axi_CTRL_BUS_RDATA[31:0],s_axi_CTRL_BUS_RRESP[1:0],s_axi_CTRL_BUS_RVALID,s_axi_CTRL_BUS_RREADY,ap_rst_n,interrupt,inStream_TVALID,inStream_TREADY,inStream_TDATA[63:0],inStream_TLAST[0:0],inStream_TKEEP[7:0],inStream_TSTRB[7:0],outStream_TVALID,outStream_TREADY,outStream_TDATA[63:0],outStream_TLAST[0:0],outStream_TKEEP[7:0],outStream_TSTRB[7:0]" */
/* synthesis syn_force_seq_prim="ap_clk" */;
  input [5:0]s_axi_CTRL_BUS_AWADDR;
  input s_axi_CTRL_BUS_AWVALID;
  output s_axi_CTRL_BUS_AWREADY;
  input [31:0]s_axi_CTRL_BUS_WDATA;
  input [3:0]s_axi_CTRL_BUS_WSTRB;
  input s_axi_CTRL_BUS_WVALID;
  output s_axi_CTRL_BUS_WREADY;
  output [1:0]s_axi_CTRL_BUS_BRESP;
  output s_axi_CTRL_BUS_BVALID;
  input s_axi_CTRL_BUS_BREADY;
  input [5:0]s_axi_CTRL_BUS_ARADDR;
  input s_axi_CTRL_BUS_ARVALID;
  output s_axi_CTRL_BUS_ARREADY;
  output [31:0]s_axi_CTRL_BUS_RDATA;
  output [1:0]s_axi_CTRL_BUS_RRESP;
  output s_axi_CTRL_BUS_RVALID;
  input s_axi_CTRL_BUS_RREADY;
  input ap_clk /* synthesis syn_isclock = 1 */;
  input ap_rst_n;
  output interrupt;
  input inStream_TVALID;
  output inStream_TREADY;
  input [63:0]inStream_TDATA;
  input [0:0]inStream_TLAST;
  input [7:0]inStream_TKEEP;
  input [7:0]inStream_TSTRB;
  output outStream_TVALID;
  input outStream_TREADY;
  output [63:0]outStream_TDATA;
  output [0:0]outStream_TLAST;
  output [7:0]outStream_TKEEP;
  output [7:0]outStream_TSTRB;
endmodule
