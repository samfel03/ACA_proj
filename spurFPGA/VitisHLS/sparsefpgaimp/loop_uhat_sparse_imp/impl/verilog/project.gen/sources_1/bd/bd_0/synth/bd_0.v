//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2023.2 (win64) Build 4029153 Fri Oct 13 20:14:34 MDT 2023
//Date        : Fri Aug  2 15:07:36 2024
//Host        : gerard running 64-bit major release  (build 9200)
//Command     : generate_target bd_0.bd
//Design      : bd_0
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "bd_0,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=bd_0,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=1,numReposBlks=1,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=1,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=USER,synth_mode=Hierarchical}" *) (* HW_HANDOFF = "bd_0.hwdef" *) 
module bd_0
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
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.AP_CLK CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.AP_CLK, ASSOCIATED_BUSIF inStream:outStream:s_axi_CTRL_BUS, ASSOCIATED_RESET ap_rst_n, CLK_DOMAIN bd_0_ap_clk_0, FREQ_HZ 100000000.0, FREQ_TOLERANCE_HZ 0, INSERT_VIP 0, PHASE 0.0" *) input ap_clk;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 RST.AP_RST_N RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME RST.AP_RST_N, INSERT_VIP 0, POLARITY ACTIVE_LOW" *) input ap_rst_n;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 inStream " *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME inStream, CLK_DOMAIN bd_0_ap_clk_0, FREQ_HZ 100000000.0, HAS_TKEEP 1, HAS_TLAST 1, HAS_TREADY 1, HAS_TSTRB 1, INSERT_VIP 0, LAYERED_METADATA undef, PHASE 0.0, TDATA_NUM_BYTES 8, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0" *) input [63:0]inStream_tdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 inStream " *) input [7:0]inStream_tkeep;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 inStream " *) input [0:0]inStream_tlast;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 inStream " *) output inStream_tready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 inStream " *) input [7:0]inStream_tstrb;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 inStream " *) input inStream_tvalid;
  (* X_INTERFACE_INFO = "xilinx.com:signal:interrupt:1.0 INTR.INTERRUPT INTERRUPT" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME INTR.INTERRUPT, PortWidth 1, SENSITIVITY LEVEL_HIGH" *) output interrupt;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 outStream " *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME outStream, CLK_DOMAIN bd_0_ap_clk_0, FREQ_HZ 100000000.0, HAS_TKEEP 1, HAS_TLAST 1, HAS_TREADY 1, HAS_TSTRB 1, INSERT_VIP 0, LAYERED_METADATA undef, PHASE 0.0, TDATA_NUM_BYTES 8, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0" *) output [63:0]outStream_tdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 outStream " *) output [7:0]outStream_tkeep;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 outStream " *) output [0:0]outStream_tlast;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 outStream " *) input outStream_tready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 outStream " *) output [7:0]outStream_tstrb;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 outStream " *) output outStream_tvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CTRL_BUS " *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s_axi_CTRL_BUS, ADDR_WIDTH 32, ARUSER_WIDTH 0, AWUSER_WIDTH 0, BUSER_WIDTH 0, CLK_DOMAIN bd_0_ap_clk_0, DATA_WIDTH 32, FREQ_HZ 100000000.0, HAS_BRESP 1, HAS_BURST 0, HAS_CACHE 0, HAS_LOCK 0, HAS_PROT 0, HAS_QOS 0, HAS_REGION 0, HAS_RRESP 1, HAS_WSTRB 1, ID_WIDTH 0, INSERT_VIP 0, MAX_BURST_LENGTH 1, NUM_READ_OUTSTANDING 1, NUM_READ_THREADS 1, NUM_WRITE_OUTSTANDING 1, NUM_WRITE_THREADS 1, PHASE 0.0, PROTOCOL AXI4LITE, READ_WRITE_MODE READ_WRITE, RUSER_BITS_PER_BYTE 0, RUSER_WIDTH 0, SUPPORTS_NARROW_BURST 0, WUSER_BITS_PER_BYTE 0, WUSER_WIDTH 0" *) input [5:0]s_axi_CTRL_BUS_araddr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CTRL_BUS " *) output s_axi_CTRL_BUS_arready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CTRL_BUS " *) input s_axi_CTRL_BUS_arvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CTRL_BUS " *) input [5:0]s_axi_CTRL_BUS_awaddr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CTRL_BUS " *) output s_axi_CTRL_BUS_awready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CTRL_BUS " *) input s_axi_CTRL_BUS_awvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CTRL_BUS " *) input s_axi_CTRL_BUS_bready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CTRL_BUS " *) output [1:0]s_axi_CTRL_BUS_bresp;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CTRL_BUS " *) output s_axi_CTRL_BUS_bvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CTRL_BUS " *) output [31:0]s_axi_CTRL_BUS_rdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CTRL_BUS " *) input s_axi_CTRL_BUS_rready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CTRL_BUS " *) output [1:0]s_axi_CTRL_BUS_rresp;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CTRL_BUS " *) output s_axi_CTRL_BUS_rvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CTRL_BUS " *) input [31:0]s_axi_CTRL_BUS_wdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CTRL_BUS " *) output s_axi_CTRL_BUS_wready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CTRL_BUS " *) input [3:0]s_axi_CTRL_BUS_wstrb;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CTRL_BUS " *) input s_axi_CTRL_BUS_wvalid;

  wire ap_clk_0_1;
  wire ap_rst_n_0_1;
  wire hls_inst_interrupt;
  wire [63:0]hls_inst_outStream_TDATA;
  wire [7:0]hls_inst_outStream_TKEEP;
  wire [0:0]hls_inst_outStream_TLAST;
  wire hls_inst_outStream_TREADY;
  wire [7:0]hls_inst_outStream_TSTRB;
  wire hls_inst_outStream_TVALID;
  wire [63:0]inStream_0_1_TDATA;
  wire [7:0]inStream_0_1_TKEEP;
  wire [0:0]inStream_0_1_TLAST;
  wire inStream_0_1_TREADY;
  wire [7:0]inStream_0_1_TSTRB;
  wire inStream_0_1_TVALID;
  wire [5:0]s_axi_CTRL_BUS_0_1_ARADDR;
  wire s_axi_CTRL_BUS_0_1_ARREADY;
  wire s_axi_CTRL_BUS_0_1_ARVALID;
  wire [5:0]s_axi_CTRL_BUS_0_1_AWADDR;
  wire s_axi_CTRL_BUS_0_1_AWREADY;
  wire s_axi_CTRL_BUS_0_1_AWVALID;
  wire s_axi_CTRL_BUS_0_1_BREADY;
  wire [1:0]s_axi_CTRL_BUS_0_1_BRESP;
  wire s_axi_CTRL_BUS_0_1_BVALID;
  wire [31:0]s_axi_CTRL_BUS_0_1_RDATA;
  wire s_axi_CTRL_BUS_0_1_RREADY;
  wire [1:0]s_axi_CTRL_BUS_0_1_RRESP;
  wire s_axi_CTRL_BUS_0_1_RVALID;
  wire [31:0]s_axi_CTRL_BUS_0_1_WDATA;
  wire s_axi_CTRL_BUS_0_1_WREADY;
  wire [3:0]s_axi_CTRL_BUS_0_1_WSTRB;
  wire s_axi_CTRL_BUS_0_1_WVALID;

  assign ap_clk_0_1 = ap_clk;
  assign ap_rst_n_0_1 = ap_rst_n;
  assign hls_inst_outStream_TREADY = outStream_tready;
  assign inStream_0_1_TDATA = inStream_tdata[63:0];
  assign inStream_0_1_TKEEP = inStream_tkeep[7:0];
  assign inStream_0_1_TLAST = inStream_tlast[0];
  assign inStream_0_1_TSTRB = inStream_tstrb[7:0];
  assign inStream_0_1_TVALID = inStream_tvalid;
  assign inStream_tready = inStream_0_1_TREADY;
  assign interrupt = hls_inst_interrupt;
  assign outStream_tdata[63:0] = hls_inst_outStream_TDATA;
  assign outStream_tkeep[7:0] = hls_inst_outStream_TKEEP;
  assign outStream_tlast[0] = hls_inst_outStream_TLAST;
  assign outStream_tstrb[7:0] = hls_inst_outStream_TSTRB;
  assign outStream_tvalid = hls_inst_outStream_TVALID;
  assign s_axi_CTRL_BUS_0_1_ARADDR = s_axi_CTRL_BUS_araddr[5:0];
  assign s_axi_CTRL_BUS_0_1_ARVALID = s_axi_CTRL_BUS_arvalid;
  assign s_axi_CTRL_BUS_0_1_AWADDR = s_axi_CTRL_BUS_awaddr[5:0];
  assign s_axi_CTRL_BUS_0_1_AWVALID = s_axi_CTRL_BUS_awvalid;
  assign s_axi_CTRL_BUS_0_1_BREADY = s_axi_CTRL_BUS_bready;
  assign s_axi_CTRL_BUS_0_1_RREADY = s_axi_CTRL_BUS_rready;
  assign s_axi_CTRL_BUS_0_1_WDATA = s_axi_CTRL_BUS_wdata[31:0];
  assign s_axi_CTRL_BUS_0_1_WSTRB = s_axi_CTRL_BUS_wstrb[3:0];
  assign s_axi_CTRL_BUS_0_1_WVALID = s_axi_CTRL_BUS_wvalid;
  assign s_axi_CTRL_BUS_arready = s_axi_CTRL_BUS_0_1_ARREADY;
  assign s_axi_CTRL_BUS_awready = s_axi_CTRL_BUS_0_1_AWREADY;
  assign s_axi_CTRL_BUS_bresp[1:0] = s_axi_CTRL_BUS_0_1_BRESP;
  assign s_axi_CTRL_BUS_bvalid = s_axi_CTRL_BUS_0_1_BVALID;
  assign s_axi_CTRL_BUS_rdata[31:0] = s_axi_CTRL_BUS_0_1_RDATA;
  assign s_axi_CTRL_BUS_rresp[1:0] = s_axi_CTRL_BUS_0_1_RRESP;
  assign s_axi_CTRL_BUS_rvalid = s_axi_CTRL_BUS_0_1_RVALID;
  assign s_axi_CTRL_BUS_wready = s_axi_CTRL_BUS_0_1_WREADY;
  bd_0_hls_inst_0 hls_inst
       (.ap_clk(ap_clk_0_1),
        .ap_rst_n(ap_rst_n_0_1),
        .inStream_TDATA(inStream_0_1_TDATA),
        .inStream_TKEEP(inStream_0_1_TKEEP),
        .inStream_TLAST(inStream_0_1_TLAST),
        .inStream_TREADY(inStream_0_1_TREADY),
        .inStream_TSTRB(inStream_0_1_TSTRB),
        .inStream_TVALID(inStream_0_1_TVALID),
        .interrupt(hls_inst_interrupt),
        .outStream_TDATA(hls_inst_outStream_TDATA),
        .outStream_TKEEP(hls_inst_outStream_TKEEP),
        .outStream_TLAST(hls_inst_outStream_TLAST),
        .outStream_TREADY(hls_inst_outStream_TREADY),
        .outStream_TSTRB(hls_inst_outStream_TSTRB),
        .outStream_TVALID(hls_inst_outStream_TVALID),
        .s_axi_CTRL_BUS_ARADDR(s_axi_CTRL_BUS_0_1_ARADDR),
        .s_axi_CTRL_BUS_ARREADY(s_axi_CTRL_BUS_0_1_ARREADY),
        .s_axi_CTRL_BUS_ARVALID(s_axi_CTRL_BUS_0_1_ARVALID),
        .s_axi_CTRL_BUS_AWADDR(s_axi_CTRL_BUS_0_1_AWADDR),
        .s_axi_CTRL_BUS_AWREADY(s_axi_CTRL_BUS_0_1_AWREADY),
        .s_axi_CTRL_BUS_AWVALID(s_axi_CTRL_BUS_0_1_AWVALID),
        .s_axi_CTRL_BUS_BREADY(s_axi_CTRL_BUS_0_1_BREADY),
        .s_axi_CTRL_BUS_BRESP(s_axi_CTRL_BUS_0_1_BRESP),
        .s_axi_CTRL_BUS_BVALID(s_axi_CTRL_BUS_0_1_BVALID),
        .s_axi_CTRL_BUS_RDATA(s_axi_CTRL_BUS_0_1_RDATA),
        .s_axi_CTRL_BUS_RREADY(s_axi_CTRL_BUS_0_1_RREADY),
        .s_axi_CTRL_BUS_RRESP(s_axi_CTRL_BUS_0_1_RRESP),
        .s_axi_CTRL_BUS_RVALID(s_axi_CTRL_BUS_0_1_RVALID),
        .s_axi_CTRL_BUS_WDATA(s_axi_CTRL_BUS_0_1_WDATA),
        .s_axi_CTRL_BUS_WREADY(s_axi_CTRL_BUS_0_1_WREADY),
        .s_axi_CTRL_BUS_WSTRB(s_axi_CTRL_BUS_0_1_WSTRB),
        .s_axi_CTRL_BUS_WVALID(s_axi_CTRL_BUS_0_1_WVALID));
endmodule
