//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2023.2 (win64) Build 4029153 Fri Oct 13 20:14:34 MDT 2023
//Date        : Fri Aug  2 15:07:36 2024
//Host        : gerard running 64-bit major release  (build 9200)
//Command     : generate_target bd_0_wrapper.bd
//Design      : bd_0_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module bd_0_wrapper
   (ap_clk,
    ap_rst_n,
    inStream_tdata,
    inStream_tkeep,
    inStream_tlast,
    inStream_tready,
    inStream_tstrb,
    inStream_tvalid,
    interrupt,
    outStream_tdata,
    outStream_tkeep,
    outStream_tlast,
    outStream_tready,
    outStream_tstrb,
    outStream_tvalid,
    s_axi_CTRL_BUS_araddr,
    s_axi_CTRL_BUS_arready,
    s_axi_CTRL_BUS_arvalid,
    s_axi_CTRL_BUS_awaddr,
    s_axi_CTRL_BUS_awready,
    s_axi_CTRL_BUS_awvalid,
    s_axi_CTRL_BUS_bready,
    s_axi_CTRL_BUS_bresp,
    s_axi_CTRL_BUS_bvalid,
    s_axi_CTRL_BUS_rdata,
    s_axi_CTRL_BUS_rready,
    s_axi_CTRL_BUS_rresp,
    s_axi_CTRL_BUS_rvalid,
    s_axi_CTRL_BUS_wdata,
    s_axi_CTRL_BUS_wready,
    s_axi_CTRL_BUS_wstrb,
    s_axi_CTRL_BUS_wvalid);
  input ap_clk;
  input ap_rst_n;
  input [63:0]inStream_tdata;
  input [7:0]inStream_tkeep;
  input [0:0]inStream_tlast;
  output inStream_tready;
  input [7:0]inStream_tstrb;
  input inStream_tvalid;
  output interrupt;
  output [63:0]outStream_tdata;
  output [7:0]outStream_tkeep;
  output [0:0]outStream_tlast;
  input outStream_tready;
  output [7:0]outStream_tstrb;
  output outStream_tvalid;
  input [5:0]s_axi_CTRL_BUS_araddr;
  output s_axi_CTRL_BUS_arready;
  input s_axi_CTRL_BUS_arvalid;
  input [5:0]s_axi_CTRL_BUS_awaddr;
  output s_axi_CTRL_BUS_awready;
  input s_axi_CTRL_BUS_awvalid;
  input s_axi_CTRL_BUS_bready;
  output [1:0]s_axi_CTRL_BUS_bresp;
  output s_axi_CTRL_BUS_bvalid;
  output [31:0]s_axi_CTRL_BUS_rdata;
  input s_axi_CTRL_BUS_rready;
  output [1:0]s_axi_CTRL_BUS_rresp;
  output s_axi_CTRL_BUS_rvalid;
  input [31:0]s_axi_CTRL_BUS_wdata;
  output s_axi_CTRL_BUS_wready;
  input [3:0]s_axi_CTRL_BUS_wstrb;
  input s_axi_CTRL_BUS_wvalid;

  wire ap_clk;
  wire ap_rst_n;
  wire [63:0]inStream_tdata;
  wire [7:0]inStream_tkeep;
  wire [0:0]inStream_tlast;
  wire inStream_tready;
  wire [7:0]inStream_tstrb;
  wire inStream_tvalid;
  wire interrupt;
  wire [63:0]outStream_tdata;
  wire [7:0]outStream_tkeep;
  wire [0:0]outStream_tlast;
  wire outStream_tready;
  wire [7:0]outStream_tstrb;
  wire outStream_tvalid;
  wire [5:0]s_axi_CTRL_BUS_araddr;
  wire s_axi_CTRL_BUS_arready;
  wire s_axi_CTRL_BUS_arvalid;
  wire [5:0]s_axi_CTRL_BUS_awaddr;
  wire s_axi_CTRL_BUS_awready;
  wire s_axi_CTRL_BUS_awvalid;
  wire s_axi_CTRL_BUS_bready;
  wire [1:0]s_axi_CTRL_BUS_bresp;
  wire s_axi_CTRL_BUS_bvalid;
  wire [31:0]s_axi_CTRL_BUS_rdata;
  wire s_axi_CTRL_BUS_rready;
  wire [1:0]s_axi_CTRL_BUS_rresp;
  wire s_axi_CTRL_BUS_rvalid;
  wire [31:0]s_axi_CTRL_BUS_wdata;
  wire s_axi_CTRL_BUS_wready;
  wire [3:0]s_axi_CTRL_BUS_wstrb;
  wire s_axi_CTRL_BUS_wvalid;

  bd_0 bd_0_i
       (.ap_clk(ap_clk),
        .ap_rst_n(ap_rst_n),
        .inStream_tdata(inStream_tdata),
        .inStream_tkeep(inStream_tkeep),
        .inStream_tlast(inStream_tlast),
        .inStream_tready(inStream_tready),
        .inStream_tstrb(inStream_tstrb),
        .inStream_tvalid(inStream_tvalid),
        .interrupt(interrupt),
        .outStream_tdata(outStream_tdata),
        .outStream_tkeep(outStream_tkeep),
        .outStream_tlast(outStream_tlast),
        .outStream_tready(outStream_tready),
        .outStream_tstrb(outStream_tstrb),
        .outStream_tvalid(outStream_tvalid),
        .s_axi_CTRL_BUS_araddr(s_axi_CTRL_BUS_araddr),
        .s_axi_CTRL_BUS_arready(s_axi_CTRL_BUS_arready),
        .s_axi_CTRL_BUS_arvalid(s_axi_CTRL_BUS_arvalid),
        .s_axi_CTRL_BUS_awaddr(s_axi_CTRL_BUS_awaddr),
        .s_axi_CTRL_BUS_awready(s_axi_CTRL_BUS_awready),
        .s_axi_CTRL_BUS_awvalid(s_axi_CTRL_BUS_awvalid),
        .s_axi_CTRL_BUS_bready(s_axi_CTRL_BUS_bready),
        .s_axi_CTRL_BUS_bresp(s_axi_CTRL_BUS_bresp),
        .s_axi_CTRL_BUS_bvalid(s_axi_CTRL_BUS_bvalid),
        .s_axi_CTRL_BUS_rdata(s_axi_CTRL_BUS_rdata),
        .s_axi_CTRL_BUS_rready(s_axi_CTRL_BUS_rready),
        .s_axi_CTRL_BUS_rresp(s_axi_CTRL_BUS_rresp),
        .s_axi_CTRL_BUS_rvalid(s_axi_CTRL_BUS_rvalid),
        .s_axi_CTRL_BUS_wdata(s_axi_CTRL_BUS_wdata),
        .s_axi_CTRL_BUS_wready(s_axi_CTRL_BUS_wready),
        .s_axi_CTRL_BUS_wstrb(s_axi_CTRL_BUS_wstrb),
        .s_axi_CTRL_BUS_wvalid(s_axi_CTRL_BUS_wvalid));
endmodule
