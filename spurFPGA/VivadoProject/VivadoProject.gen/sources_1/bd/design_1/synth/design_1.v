//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2023.2 (win64) Build 4029153 Fri Oct 13 20:14:34 MDT 2023
//Date        : Tue Jul  9 15:46:16 2024
//Host        : gerard running 64-bit major release  (build 9200)
//Command     : generate_target design_1.bd
//Design      : design_1
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "design_1,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=design_1,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=3,numReposBlks=3,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=1,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=USER,da_board_cnt=6,da_clkrst_cnt=2,synth_mode=Hierarchical}" *) (* HW_HANDOFF = "design_1.hwdef" *) 
module design_1
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
  (* X_INTERFACE_INFO = "xilinx.com:signal:data:1.0 DATA.ELEMENTS_0 DATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME DATA.ELEMENTS_0, LAYERED_METADATA undef" *) input [31:0]ELEMENTS_0;
  (* X_INTERFACE_INFO = "xilinx.com:signal:data:1.0 DATA.L_0 DATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME DATA.L_0, LAYERED_METADATA undef" *) input [63:0]L_0;
  (* X_INTERFACE_INFO = "xilinx.com:signal:data:1.0 DATA.L_EXP_0 DATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME DATA.L_EXP_0, LAYERED_METADATA undef" *) input [63:0]L_exp_0;
  (* X_INTERFACE_INFO = "xilinx.com:signal:data:1.0 DATA.R_0 DATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME DATA.R_0, LAYERED_METADATA undef" *) input [63:0]R_0;
  (* X_INTERFACE_INFO = "xilinx.com:signal:data:1.0 DATA.R_EXP_0 DATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME DATA.R_EXP_0, LAYERED_METADATA undef" *) input [63:0]R_exp_0;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.CLK_100MHZ CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.CLK_100MHZ, CLK_DOMAIN design_1_clk_100MHz, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, INSERT_VIP 0, PHASE 0.0" *) input clk_100MHz;
  (* X_INTERFACE_INFO = "xilinx.com:signal:data:1.0 DATA.COLINDEX_0 DATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME DATA.COLINDEX_0, LAYERED_METADATA undef" *) input [31:0]colIndex_0;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 RST.RESET_RTL_0 RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME RST.RESET_RTL_0, INSERT_VIP 0, POLARITY ACTIVE_HIGH" *) input reset_rtl_0;
  (* X_INTERFACE_INFO = "xilinx.com:signal:data:1.0 DATA.ROWSTART_0 DATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME DATA.ROWSTART_0, LAYERED_METADATA undef" *) input [31:0]rowStart_0;
  (* X_INTERFACE_INFO = "xilinx.com:signal:data:1.0 DATA.TOL_0 DATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME DATA.TOL_0, LAYERED_METADATA undef" *) input [63:0]tol_0;
  (* X_INTERFACE_INFO = "xilinx.com:signal:data:1.0 DATA.UHAT_I_I_0 DATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME DATA.UHAT_I_I_0, LAYERED_METADATA undef" *) input [63:0]uhat_i_i_0;
  (* X_INTERFACE_INFO = "xilinx.com:signal:data:1.0 DATA.UHAT_I_O_0 DATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME DATA.UHAT_I_O_0, LAYERED_METADATA undef" *) output [63:0]uhat_i_o_0;
  output uhat_i_o_ap_vld_0;
  (* X_INTERFACE_INFO = "xilinx.com:signal:data:1.0 DATA.VALUE_R_0 DATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME DATA.VALUE_R_0, LAYERED_METADATA undef" *) input [63:0]value_r_0;

  wire [31:0]ELEMENTS_0_1;
  wire [63:0]L_0_1;
  wire [63:0]L_exp_0_1;
  wire [63:0]R_0_1;
  wire [63:0]R_exp_0_1;
  wire clk_100MHz_1;
  wire clk_wiz_clk_out1;
  wire clk_wiz_locked;
  wire [31:0]colIndex_0_1;
  wire reset_rtl_0_1;
  wire [31:0]rowStart_0_1;
  wire [0:0]rst_clk_wiz_100M_peripheral_reset;
  wire [63:0]tol_0_1;
  wire [63:0]uhat_i_i_0_1;
  wire [63:0]value_r_0_1;

  assign ELEMENTS_0_1 = ELEMENTS_0[31:0];
  assign L_0_1 = L_0[63:0];
  assign L_exp_0_1 = L_exp_0[63:0];
  assign R_0_1 = R_0[63:0];
  assign R_exp_0_1 = R_exp_0[63:0];
  assign clk_100MHz_1 = clk_100MHz;
  assign colIndex_0_1 = colIndex_0[31:0];
  assign reset_rtl_0_1 = reset_rtl_0;
  assign rowStart_0_1 = rowStart_0[31:0];
  assign tol_0_1 = tol_0[63:0];
  assign uhat_i_i_0_1 = uhat_i_i_0[63:0];
  assign value_r_0_1 = value_r_0[63:0];
  design_1_clk_wiz_1 clk_wiz
       (.clk_in1(clk_100MHz_1),
        .clk_out1(clk_wiz_clk_out1),
        .locked(clk_wiz_locked),
        .reset(reset_rtl_0_1));
  design_1_loop_uhat_sparse_0_0 loop_uhat_sparse_0
       (.ELEMENTS(ELEMENTS_0_1),
        .L_exp(L_exp_0_1),
        .R_exp(R_exp_0_1),
        .ap_clk(clk_wiz_clk_out1),
        .ap_rst_n(1'b0),
        .ap_start(1'b0),
        .colIndex(colIndex_0_1),
        .m_axi_gmem_ARREADY(1'b0),
        .m_axi_gmem_AWREADY(1'b0),
        .m_axi_gmem_BID(1'b0),
        .m_axi_gmem_BRESP({1'b0,1'b0}),
        .m_axi_gmem_BVALID(1'b0),
        .m_axi_gmem_RDATA({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .m_axi_gmem_RID(1'b0),
        .m_axi_gmem_RLAST(1'b0),
        .m_axi_gmem_RRESP({1'b0,1'b0}),
        .m_axi_gmem_RVALID(1'b0),
        .m_axi_gmem_WREADY(1'b0),
        .rowStart(rowStart_0_1),
        .s_axi_control_ARADDR({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .s_axi_control_ARVALID(1'b0),
        .s_axi_control_AWADDR({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .s_axi_control_AWVALID(1'b0),
        .s_axi_control_BREADY(1'b0),
        .s_axi_control_RREADY(1'b0),
        .s_axi_control_WDATA({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .s_axi_control_WSTRB({1'b1,1'b1,1'b1,1'b1}),
        .s_axi_control_WVALID(1'b0),
        .tol(tol_0_1),
        .value_r(value_r_0_1));
  design_1_rst_clk_wiz_100M_1 rst_clk_wiz_100M
       (.aux_reset_in(1'b1),
        .dcm_locked(clk_wiz_locked),
        .ext_reset_in(reset_rtl_0_1),
        .mb_debug_sys_rst(1'b0),
        .peripheral_reset(rst_clk_wiz_100M_peripheral_reset),
        .slowest_sync_clk(clk_wiz_clk_out1));
endmodule
