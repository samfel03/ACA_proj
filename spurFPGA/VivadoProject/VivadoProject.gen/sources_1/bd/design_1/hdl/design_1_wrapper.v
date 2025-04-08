//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2023.2 (win64) Build 4029153 Fri Oct 13 20:14:34 MDT 2023
//Date        : Tue Jul  9 15:46:16 2024
//Host        : gerard running 64-bit major release  (build 9200)
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_1_wrapper
   (ELEMENTS_0,
    L_0,
    L_exp_0,
    R_0,
    R_exp_0,
    clk_100MHz,
    colIndex_0,
    reset_rtl_0,
    rowStart_0,
    tol_0,
    uhat_i_i_0,
    uhat_i_o_0,
    uhat_i_o_ap_vld_0,
    value_r_0);
  input [31:0]ELEMENTS_0;
  input [63:0]L_0;
  input [63:0]L_exp_0;
  input [63:0]R_0;
  input [63:0]R_exp_0;
  input clk_100MHz;
  input [31:0]colIndex_0;
  input reset_rtl_0;
  input [31:0]rowStart_0;
  input [63:0]tol_0;
  input [63:0]uhat_i_i_0;
  output [63:0]uhat_i_o_0;
  output uhat_i_o_ap_vld_0;
  input [63:0]value_r_0;

  wire [31:0]ELEMENTS_0;
  wire [63:0]L_0;
  wire [63:0]L_exp_0;
  wire [63:0]R_0;
  wire [63:0]R_exp_0;
  wire clk_100MHz;
  wire [31:0]colIndex_0;
  wire reset_rtl_0;
  wire [31:0]rowStart_0;
  wire [63:0]tol_0;
  wire [63:0]uhat_i_i_0;
  wire [63:0]uhat_i_o_0;
  wire uhat_i_o_ap_vld_0;
  wire [63:0]value_r_0;

  design_1 design_1_i
       (.ELEMENTS_0(ELEMENTS_0),
        .L_0(L_0),
        .L_exp_0(L_exp_0),
        .R_0(R_0),
        .R_exp_0(R_exp_0),
        .clk_100MHz(clk_100MHz),
        .colIndex_0(colIndex_0),
        .reset_rtl_0(reset_rtl_0),
        .rowStart_0(rowStart_0),
        .tol_0(tol_0),
        .uhat_i_i_0(uhat_i_i_0),
        .uhat_i_o_0(uhat_i_o_0),
        .uhat_i_o_ap_vld_0(uhat_i_o_ap_vld_0),
        .value_r_0(value_r_0));
endmodule
