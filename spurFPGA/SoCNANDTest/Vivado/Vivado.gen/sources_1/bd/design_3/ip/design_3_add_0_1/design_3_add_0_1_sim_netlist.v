// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2023.2 (win64) Build 4029153 Fri Oct 13 20:14:34 MDT 2023
// Date        : Wed Jul 17 12:15:43 2024
// Host        : gerard running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               c:/Research/CU-Spur-Sean/spurFPGA/SoCNANDTest/Vivado/Vivado.gen/sources_1/bd/design_3/ip/design_3_add_0_1/design_3_add_0_1_sim_netlist.v
// Design      : design_3_add_0_1
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7z007sclg400-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "design_3_add_0_1,add,{}" *) (* DowngradeIPIdentifiedWarnings = "yes" *) (* IP_DEFINITION_SOURCE = "HLS" *) 
(* X_CORE_INFO = "add,Vivado 2023.2" *) (* hls_module = "yes" *) 
(* NotValidForBitStream *)
module design_3_add_0_1
   (s_axi_CRTLS_AWADDR,
    s_axi_CRTLS_AWVALID,
    s_axi_CRTLS_AWREADY,
    s_axi_CRTLS_WDATA,
    s_axi_CRTLS_WSTRB,
    s_axi_CRTLS_WVALID,
    s_axi_CRTLS_WREADY,
    s_axi_CRTLS_BRESP,
    s_axi_CRTLS_BVALID,
    s_axi_CRTLS_BREADY,
    s_axi_CRTLS_ARADDR,
    s_axi_CRTLS_ARVALID,
    s_axi_CRTLS_ARREADY,
    s_axi_CRTLS_RDATA,
    s_axi_CRTLS_RRESP,
    s_axi_CRTLS_RVALID,
    s_axi_CRTLS_RREADY,
    ap_clk,
    ap_rst_n,
    interrupt);
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CRTLS AWADDR" *) input [5:0]s_axi_CRTLS_AWADDR;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CRTLS AWVALID" *) input s_axi_CRTLS_AWVALID;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CRTLS AWREADY" *) output s_axi_CRTLS_AWREADY;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CRTLS WDATA" *) input [31:0]s_axi_CRTLS_WDATA;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CRTLS WSTRB" *) input [3:0]s_axi_CRTLS_WSTRB;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CRTLS WVALID" *) input s_axi_CRTLS_WVALID;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CRTLS WREADY" *) output s_axi_CRTLS_WREADY;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CRTLS BRESP" *) output [1:0]s_axi_CRTLS_BRESP;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CRTLS BVALID" *) output s_axi_CRTLS_BVALID;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CRTLS BREADY" *) input s_axi_CRTLS_BREADY;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CRTLS ARADDR" *) input [5:0]s_axi_CRTLS_ARADDR;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CRTLS ARVALID" *) input s_axi_CRTLS_ARVALID;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CRTLS ARREADY" *) output s_axi_CRTLS_ARREADY;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CRTLS RDATA" *) output [31:0]s_axi_CRTLS_RDATA;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CRTLS RRESP" *) output [1:0]s_axi_CRTLS_RRESP;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CRTLS RVALID" *) output s_axi_CRTLS_RVALID;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_CRTLS RREADY" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s_axi_CRTLS, ADDR_WIDTH 6, DATA_WIDTH 32, PROTOCOL AXI4LITE, READ_WRITE_MODE READ_WRITE, FREQ_HZ 50000000, ID_WIDTH 0, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.0, CLK_DOMAIN design_3_processing_system7_0_0_FCLK_CLK0, NUM_READ_THREADS 4, NUM_WRITE_THREADS 4, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *) input s_axi_CRTLS_RREADY;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 ap_clk CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_clk, ASSOCIATED_BUSIF s_axi_CRTLS, ASSOCIATED_RESET ap_rst_n, FREQ_HZ 50000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN design_3_processing_system7_0_0_FCLK_CLK0, INSERT_VIP 0" *) input ap_clk;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 ap_rst_n RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_rst_n, POLARITY ACTIVE_LOW, INSERT_VIP 0" *) input ap_rst_n;
  (* X_INTERFACE_INFO = "xilinx.com:signal:interrupt:1.0 interrupt INTERRUPT" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME interrupt, SENSITIVITY LEVEL_HIGH, PortWidth 1" *) output interrupt;

  wire \<const0> ;
  wire ap_clk;
  wire ap_rst_n;
  wire interrupt;
  wire [5:0]s_axi_CRTLS_ARADDR;
  wire s_axi_CRTLS_ARREADY;
  wire s_axi_CRTLS_ARVALID;
  wire [5:0]s_axi_CRTLS_AWADDR;
  wire s_axi_CRTLS_AWREADY;
  wire s_axi_CRTLS_AWVALID;
  wire s_axi_CRTLS_BREADY;
  wire s_axi_CRTLS_BVALID;
  wire [31:0]s_axi_CRTLS_RDATA;
  wire s_axi_CRTLS_RREADY;
  wire s_axi_CRTLS_RVALID;
  wire [31:0]s_axi_CRTLS_WDATA;
  wire s_axi_CRTLS_WREADY;
  wire [3:0]s_axi_CRTLS_WSTRB;
  wire s_axi_CRTLS_WVALID;
  wire [1:0]NLW_inst_s_axi_CRTLS_BRESP_UNCONNECTED;
  wire [1:0]NLW_inst_s_axi_CRTLS_RRESP_UNCONNECTED;

  assign s_axi_CRTLS_BRESP[1] = \<const0> ;
  assign s_axi_CRTLS_BRESP[0] = \<const0> ;
  assign s_axi_CRTLS_RRESP[1] = \<const0> ;
  assign s_axi_CRTLS_RRESP[0] = \<const0> ;
  GND GND
       (.G(\<const0> ));
  (* C_S_AXI_CRTLS_ADDR_WIDTH = "6" *) 
  (* C_S_AXI_CRTLS_DATA_WIDTH = "32" *) 
  (* C_S_AXI_CRTLS_WSTRB_WIDTH = "4" *) 
  (* C_S_AXI_DATA_WIDTH = "32" *) 
  (* C_S_AXI_WSTRB_WIDTH = "4" *) 
  (* SDX_KERNEL = "true" *) 
  (* SDX_KERNEL_SYNTH_INST = "inst" *) 
  (* SDX_KERNEL_TYPE = "hls" *) 
  design_3_add_0_1_add inst
       (.ap_clk(ap_clk),
        .ap_rst_n(ap_rst_n),
        .interrupt(interrupt),
        .s_axi_CRTLS_ARADDR(s_axi_CRTLS_ARADDR),
        .s_axi_CRTLS_ARREADY(s_axi_CRTLS_ARREADY),
        .s_axi_CRTLS_ARVALID(s_axi_CRTLS_ARVALID),
        .s_axi_CRTLS_AWADDR(s_axi_CRTLS_AWADDR),
        .s_axi_CRTLS_AWREADY(s_axi_CRTLS_AWREADY),
        .s_axi_CRTLS_AWVALID(s_axi_CRTLS_AWVALID),
        .s_axi_CRTLS_BREADY(s_axi_CRTLS_BREADY),
        .s_axi_CRTLS_BRESP(NLW_inst_s_axi_CRTLS_BRESP_UNCONNECTED[1:0]),
        .s_axi_CRTLS_BVALID(s_axi_CRTLS_BVALID),
        .s_axi_CRTLS_RDATA(s_axi_CRTLS_RDATA),
        .s_axi_CRTLS_RREADY(s_axi_CRTLS_RREADY),
        .s_axi_CRTLS_RRESP(NLW_inst_s_axi_CRTLS_RRESP_UNCONNECTED[1:0]),
        .s_axi_CRTLS_RVALID(s_axi_CRTLS_RVALID),
        .s_axi_CRTLS_WDATA(s_axi_CRTLS_WDATA),
        .s_axi_CRTLS_WREADY(s_axi_CRTLS_WREADY),
        .s_axi_CRTLS_WSTRB(s_axi_CRTLS_WSTRB),
        .s_axi_CRTLS_WVALID(s_axi_CRTLS_WVALID));
endmodule

(* C_S_AXI_CRTLS_ADDR_WIDTH = "6" *) (* C_S_AXI_CRTLS_DATA_WIDTH = "32" *) (* C_S_AXI_CRTLS_WSTRB_WIDTH = "4" *) 
(* C_S_AXI_DATA_WIDTH = "32" *) (* C_S_AXI_WSTRB_WIDTH = "4" *) (* ORIG_REF_NAME = "add" *) 
(* hls_module = "yes" *) 
module design_3_add_0_1_add
   (s_axi_CRTLS_AWVALID,
    s_axi_CRTLS_AWREADY,
    s_axi_CRTLS_AWADDR,
    s_axi_CRTLS_WVALID,
    s_axi_CRTLS_WREADY,
    s_axi_CRTLS_WDATA,
    s_axi_CRTLS_WSTRB,
    s_axi_CRTLS_ARVALID,
    s_axi_CRTLS_ARREADY,
    s_axi_CRTLS_ARADDR,
    s_axi_CRTLS_RVALID,
    s_axi_CRTLS_RREADY,
    s_axi_CRTLS_RDATA,
    s_axi_CRTLS_RRESP,
    s_axi_CRTLS_BVALID,
    s_axi_CRTLS_BREADY,
    s_axi_CRTLS_BRESP,
    ap_clk,
    ap_rst_n,
    interrupt);
  input s_axi_CRTLS_AWVALID;
  output s_axi_CRTLS_AWREADY;
  input [5:0]s_axi_CRTLS_AWADDR;
  input s_axi_CRTLS_WVALID;
  output s_axi_CRTLS_WREADY;
  input [31:0]s_axi_CRTLS_WDATA;
  input [3:0]s_axi_CRTLS_WSTRB;
  input s_axi_CRTLS_ARVALID;
  output s_axi_CRTLS_ARREADY;
  input [5:0]s_axi_CRTLS_ARADDR;
  output s_axi_CRTLS_RVALID;
  input s_axi_CRTLS_RREADY;
  output [31:0]s_axi_CRTLS_RDATA;
  output [1:0]s_axi_CRTLS_RRESP;
  output s_axi_CRTLS_BVALID;
  input s_axi_CRTLS_BREADY;
  output [1:0]s_axi_CRTLS_BRESP;
  input ap_clk;
  input ap_rst_n;
  output interrupt;

  wire \<const0> ;
  wire ap_clk;
  wire ap_rst_n;
  wire interrupt;
  wire [5:0]s_axi_CRTLS_ARADDR;
  wire s_axi_CRTLS_ARREADY;
  wire s_axi_CRTLS_ARVALID;
  wire [5:0]s_axi_CRTLS_AWADDR;
  wire s_axi_CRTLS_AWREADY;
  wire s_axi_CRTLS_AWVALID;
  wire s_axi_CRTLS_BREADY;
  wire s_axi_CRTLS_BVALID;
  wire [31:0]s_axi_CRTLS_RDATA;
  wire s_axi_CRTLS_RREADY;
  wire s_axi_CRTLS_RVALID;
  wire [31:0]s_axi_CRTLS_WDATA;
  wire s_axi_CRTLS_WREADY;
  wire [3:0]s_axi_CRTLS_WSTRB;
  wire s_axi_CRTLS_WVALID;

  assign s_axi_CRTLS_BRESP[1] = \<const0> ;
  assign s_axi_CRTLS_BRESP[0] = \<const0> ;
  assign s_axi_CRTLS_RRESP[1] = \<const0> ;
  assign s_axi_CRTLS_RRESP[0] = \<const0> ;
  design_3_add_0_1_add_CRTLS_s_axi CRTLS_s_axi_U
       (.\FSM_onehot_rstate_reg[1]_0 (s_axi_CRTLS_ARREADY),
        .\FSM_onehot_wstate_reg[1]_0 (s_axi_CRTLS_AWREADY),
        .\FSM_onehot_wstate_reg[2]_0 (s_axi_CRTLS_WREADY),
        .ap_clk(ap_clk),
        .ap_rst_n(ap_rst_n),
        .interrupt(interrupt),
        .s_axi_CRTLS_ARADDR(s_axi_CRTLS_ARADDR),
        .s_axi_CRTLS_ARVALID(s_axi_CRTLS_ARVALID),
        .s_axi_CRTLS_AWADDR(s_axi_CRTLS_AWADDR),
        .s_axi_CRTLS_AWVALID(s_axi_CRTLS_AWVALID),
        .s_axi_CRTLS_BREADY(s_axi_CRTLS_BREADY),
        .s_axi_CRTLS_BVALID(s_axi_CRTLS_BVALID),
        .s_axi_CRTLS_RDATA(s_axi_CRTLS_RDATA),
        .s_axi_CRTLS_RREADY(s_axi_CRTLS_RREADY),
        .s_axi_CRTLS_RVALID(s_axi_CRTLS_RVALID),
        .s_axi_CRTLS_WDATA(s_axi_CRTLS_WDATA),
        .s_axi_CRTLS_WSTRB(s_axi_CRTLS_WSTRB),
        .s_axi_CRTLS_WVALID(s_axi_CRTLS_WVALID));
  GND GND
       (.G(\<const0> ));
endmodule

(* ORIG_REF_NAME = "add_CRTLS_s_axi" *) 
module design_3_add_0_1_add_CRTLS_s_axi
   (interrupt,
    \FSM_onehot_rstate_reg[1]_0 ,
    \FSM_onehot_wstate_reg[2]_0 ,
    s_axi_CRTLS_BVALID,
    \FSM_onehot_wstate_reg[1]_0 ,
    s_axi_CRTLS_RVALID,
    s_axi_CRTLS_RDATA,
    ap_clk,
    ap_rst_n,
    s_axi_CRTLS_WDATA,
    s_axi_CRTLS_WSTRB,
    s_axi_CRTLS_ARVALID,
    s_axi_CRTLS_ARADDR,
    s_axi_CRTLS_WVALID,
    s_axi_CRTLS_AWADDR,
    s_axi_CRTLS_RREADY,
    s_axi_CRTLS_AWVALID,
    s_axi_CRTLS_BREADY);
  output interrupt;
  output \FSM_onehot_rstate_reg[1]_0 ;
  output \FSM_onehot_wstate_reg[2]_0 ;
  output s_axi_CRTLS_BVALID;
  output \FSM_onehot_wstate_reg[1]_0 ;
  output s_axi_CRTLS_RVALID;
  output [31:0]s_axi_CRTLS_RDATA;
  input ap_clk;
  input ap_rst_n;
  input [31:0]s_axi_CRTLS_WDATA;
  input [3:0]s_axi_CRTLS_WSTRB;
  input s_axi_CRTLS_ARVALID;
  input [5:0]s_axi_CRTLS_ARADDR;
  input s_axi_CRTLS_WVALID;
  input [5:0]s_axi_CRTLS_AWADDR;
  input s_axi_CRTLS_RREADY;
  input s_axi_CRTLS_AWVALID;
  input s_axi_CRTLS_BREADY;

  wire \FSM_onehot_rstate[1]_i_1_n_0 ;
  wire \FSM_onehot_rstate[2]_i_1_n_0 ;
  wire \FSM_onehot_rstate_reg[1]_0 ;
  wire \FSM_onehot_wstate[1]_i_2_n_0 ;
  wire \FSM_onehot_wstate[2]_i_1_n_0 ;
  wire \FSM_onehot_wstate[3]_i_1_n_0 ;
  wire \FSM_onehot_wstate_reg[1]_0 ;
  wire \FSM_onehot_wstate_reg[2]_0 ;
  wire [31:0]a;
  wire ap_clk;
  wire ap_done;
  wire [31:0]ap_return;
  wire ap_rst_n;
  wire ap_rst_n_inv;
  wire ar_hs;
  wire auto_restart_status_reg_n_0;
  wire [31:0]b;
  wire [31:0]int_a0;
  wire \int_a[31]_i_3_n_0 ;
  wire int_ap_ready;
  wire int_ap_ready_i_1_n_0;
  wire [31:0]int_ap_return;
  wire \int_ap_return[11]_i_2_n_0 ;
  wire \int_ap_return[11]_i_3_n_0 ;
  wire \int_ap_return[11]_i_4_n_0 ;
  wire \int_ap_return[11]_i_5_n_0 ;
  wire \int_ap_return[15]_i_2_n_0 ;
  wire \int_ap_return[15]_i_3_n_0 ;
  wire \int_ap_return[15]_i_4_n_0 ;
  wire \int_ap_return[15]_i_5_n_0 ;
  wire \int_ap_return[19]_i_2_n_0 ;
  wire \int_ap_return[19]_i_3_n_0 ;
  wire \int_ap_return[19]_i_4_n_0 ;
  wire \int_ap_return[19]_i_5_n_0 ;
  wire \int_ap_return[23]_i_2_n_0 ;
  wire \int_ap_return[23]_i_3_n_0 ;
  wire \int_ap_return[23]_i_4_n_0 ;
  wire \int_ap_return[23]_i_5_n_0 ;
  wire \int_ap_return[27]_i_2_n_0 ;
  wire \int_ap_return[27]_i_3_n_0 ;
  wire \int_ap_return[27]_i_4_n_0 ;
  wire \int_ap_return[27]_i_5_n_0 ;
  wire \int_ap_return[31]_i_2_n_0 ;
  wire \int_ap_return[31]_i_3_n_0 ;
  wire \int_ap_return[31]_i_4_n_0 ;
  wire \int_ap_return[31]_i_5_n_0 ;
  wire \int_ap_return[3]_i_2_n_0 ;
  wire \int_ap_return[3]_i_3_n_0 ;
  wire \int_ap_return[3]_i_4_n_0 ;
  wire \int_ap_return[3]_i_5_n_0 ;
  wire \int_ap_return[7]_i_2_n_0 ;
  wire \int_ap_return[7]_i_3_n_0 ;
  wire \int_ap_return[7]_i_4_n_0 ;
  wire \int_ap_return[7]_i_5_n_0 ;
  wire \int_ap_return_reg[11]_i_1_n_0 ;
  wire \int_ap_return_reg[11]_i_1_n_1 ;
  wire \int_ap_return_reg[11]_i_1_n_2 ;
  wire \int_ap_return_reg[11]_i_1_n_3 ;
  wire \int_ap_return_reg[15]_i_1_n_0 ;
  wire \int_ap_return_reg[15]_i_1_n_1 ;
  wire \int_ap_return_reg[15]_i_1_n_2 ;
  wire \int_ap_return_reg[15]_i_1_n_3 ;
  wire \int_ap_return_reg[19]_i_1_n_0 ;
  wire \int_ap_return_reg[19]_i_1_n_1 ;
  wire \int_ap_return_reg[19]_i_1_n_2 ;
  wire \int_ap_return_reg[19]_i_1_n_3 ;
  wire \int_ap_return_reg[23]_i_1_n_0 ;
  wire \int_ap_return_reg[23]_i_1_n_1 ;
  wire \int_ap_return_reg[23]_i_1_n_2 ;
  wire \int_ap_return_reg[23]_i_1_n_3 ;
  wire \int_ap_return_reg[27]_i_1_n_0 ;
  wire \int_ap_return_reg[27]_i_1_n_1 ;
  wire \int_ap_return_reg[27]_i_1_n_2 ;
  wire \int_ap_return_reg[27]_i_1_n_3 ;
  wire \int_ap_return_reg[31]_i_1_n_1 ;
  wire \int_ap_return_reg[31]_i_1_n_2 ;
  wire \int_ap_return_reg[31]_i_1_n_3 ;
  wire \int_ap_return_reg[3]_i_1_n_0 ;
  wire \int_ap_return_reg[3]_i_1_n_1 ;
  wire \int_ap_return_reg[3]_i_1_n_2 ;
  wire \int_ap_return_reg[3]_i_1_n_3 ;
  wire \int_ap_return_reg[7]_i_1_n_0 ;
  wire \int_ap_return_reg[7]_i_1_n_1 ;
  wire \int_ap_return_reg[7]_i_1_n_2 ;
  wire \int_ap_return_reg[7]_i_1_n_3 ;
  wire int_ap_start1;
  wire int_ap_start_i_1_n_0;
  wire int_auto_restart_i_1_n_0;
  wire int_auto_restart_i_2_n_0;
  wire [31:0]int_b0;
  wire \int_b[31]_i_1_n_0 ;
  wire \int_b[31]_i_3_n_0 ;
  wire int_gie_i_1_n_0;
  wire int_gie_reg_n_0;
  wire int_ier;
  wire int_ier_i_1_n_0;
  wire int_interrupt0;
  wire int_interrupt1;
  wire int_isr6_out;
  wire int_isr_i_1_n_0;
  wire int_isr_i_2_n_0;
  wire int_task_ap_done;
  wire int_task_ap_done0__3;
  wire int_task_ap_done_i_1_n_0;
  wire int_task_ap_done_i_3_n_0;
  wire interrupt;
  wire p_0_in;
  wire [7:2]p_3_in;
  wire [9:0]rdata;
  wire \rdata[0]_i_2_n_0 ;
  wire \rdata[0]_i_3_n_0 ;
  wire \rdata[10]_i_1_n_0 ;
  wire \rdata[11]_i_1_n_0 ;
  wire \rdata[12]_i_1_n_0 ;
  wire \rdata[13]_i_1_n_0 ;
  wire \rdata[14]_i_1_n_0 ;
  wire \rdata[15]_i_1_n_0 ;
  wire \rdata[16]_i_1_n_0 ;
  wire \rdata[17]_i_1_n_0 ;
  wire \rdata[18]_i_1_n_0 ;
  wire \rdata[19]_i_1_n_0 ;
  wire \rdata[1]_i_2_n_0 ;
  wire \rdata[20]_i_1_n_0 ;
  wire \rdata[21]_i_1_n_0 ;
  wire \rdata[22]_i_1_n_0 ;
  wire \rdata[23]_i_1_n_0 ;
  wire \rdata[24]_i_1_n_0 ;
  wire \rdata[25]_i_1_n_0 ;
  wire \rdata[26]_i_1_n_0 ;
  wire \rdata[27]_i_1_n_0 ;
  wire \rdata[28]_i_1_n_0 ;
  wire \rdata[29]_i_1_n_0 ;
  wire \rdata[2]_i_2_n_0 ;
  wire \rdata[30]_i_1_n_0 ;
  wire \rdata[31]_i_1_n_0 ;
  wire \rdata[31]_i_3_n_0 ;
  wire \rdata[31]_i_4_n_0 ;
  wire \rdata[31]_i_5_n_0 ;
  wire \rdata[3]_i_2_n_0 ;
  wire \rdata[4]_i_1_n_0 ;
  wire \rdata[5]_i_1_n_0 ;
  wire \rdata[6]_i_1_n_0 ;
  wire \rdata[7]_i_2_n_0 ;
  wire \rdata[8]_i_1_n_0 ;
  wire \rdata[9]_i_2_n_0 ;
  wire \rdata[9]_i_3_n_0 ;
  wire [5:0]s_axi_CRTLS_ARADDR;
  wire s_axi_CRTLS_ARVALID;
  wire [5:0]s_axi_CRTLS_AWADDR;
  wire s_axi_CRTLS_AWVALID;
  wire s_axi_CRTLS_BREADY;
  wire s_axi_CRTLS_BVALID;
  wire [31:0]s_axi_CRTLS_RDATA;
  wire s_axi_CRTLS_RREADY;
  wire s_axi_CRTLS_RVALID;
  wire [31:0]s_axi_CRTLS_WDATA;
  wire [3:0]s_axi_CRTLS_WSTRB;
  wire s_axi_CRTLS_WVALID;
  wire waddr;
  wire \waddr_reg_n_0_[0] ;
  wire \waddr_reg_n_0_[1] ;
  wire \waddr_reg_n_0_[2] ;
  wire \waddr_reg_n_0_[3] ;
  wire \waddr_reg_n_0_[4] ;
  wire \waddr_reg_n_0_[5] ;
  wire [3:3]\NLW_int_ap_return_reg[31]_i_1_CO_UNCONNECTED ;

  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT4 #(
    .INIT(16'hF747)) 
    \FSM_onehot_rstate[1]_i_1 
       (.I0(s_axi_CRTLS_ARVALID),
        .I1(\FSM_onehot_rstate_reg[1]_0 ),
        .I2(s_axi_CRTLS_RVALID),
        .I3(s_axi_CRTLS_RREADY),
        .O(\FSM_onehot_rstate[1]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT4 #(
    .INIT(16'h88F8)) 
    \FSM_onehot_rstate[2]_i_1 
       (.I0(s_axi_CRTLS_ARVALID),
        .I1(\FSM_onehot_rstate_reg[1]_0 ),
        .I2(s_axi_CRTLS_RVALID),
        .I3(s_axi_CRTLS_RREADY),
        .O(\FSM_onehot_rstate[2]_i_1_n_0 ));
  (* FSM_ENCODED_STATES = "RDIDLE:010,RDDATA:100,iSTATE:001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_rstate_reg[1] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\FSM_onehot_rstate[1]_i_1_n_0 ),
        .Q(\FSM_onehot_rstate_reg[1]_0 ),
        .R(ap_rst_n_inv));
  (* FSM_ENCODED_STATES = "RDIDLE:010,RDDATA:100,iSTATE:001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_rstate_reg[2] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\FSM_onehot_rstate[2]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RVALID),
        .R(ap_rst_n_inv));
  LUT1 #(
    .INIT(2'h1)) 
    \FSM_onehot_wstate[1]_i_1 
       (.I0(ap_rst_n),
        .O(ap_rst_n_inv));
  LUT5 #(
    .INIT(32'h888BFF8B)) 
    \FSM_onehot_wstate[1]_i_2 
       (.I0(s_axi_CRTLS_BREADY),
        .I1(s_axi_CRTLS_BVALID),
        .I2(\FSM_onehot_wstate_reg[2]_0 ),
        .I3(\FSM_onehot_wstate_reg[1]_0 ),
        .I4(s_axi_CRTLS_AWVALID),
        .O(\FSM_onehot_wstate[1]_i_2_n_0 ));
  LUT4 #(
    .INIT(16'h8F88)) 
    \FSM_onehot_wstate[2]_i_1 
       (.I0(s_axi_CRTLS_AWVALID),
        .I1(\FSM_onehot_wstate_reg[1]_0 ),
        .I2(s_axi_CRTLS_WVALID),
        .I3(\FSM_onehot_wstate_reg[2]_0 ),
        .O(\FSM_onehot_wstate[2]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h8F88)) 
    \FSM_onehot_wstate[3]_i_1 
       (.I0(s_axi_CRTLS_WVALID),
        .I1(\FSM_onehot_wstate_reg[2]_0 ),
        .I2(s_axi_CRTLS_BREADY),
        .I3(s_axi_CRTLS_BVALID),
        .O(\FSM_onehot_wstate[3]_i_1_n_0 ));
  (* FSM_ENCODED_STATES = "WRDATA:0100,WRRESP:1000,WRIDLE:0010,iSTATE:0001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_wstate_reg[1] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\FSM_onehot_wstate[1]_i_2_n_0 ),
        .Q(\FSM_onehot_wstate_reg[1]_0 ),
        .R(ap_rst_n_inv));
  (* FSM_ENCODED_STATES = "WRDATA:0100,WRRESP:1000,WRIDLE:0010,iSTATE:0001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_wstate_reg[2] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\FSM_onehot_wstate[2]_i_1_n_0 ),
        .Q(\FSM_onehot_wstate_reg[2]_0 ),
        .R(ap_rst_n_inv));
  (* FSM_ENCODED_STATES = "WRDATA:0100,WRRESP:1000,WRIDLE:0010,iSTATE:0001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_wstate_reg[3] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\FSM_onehot_wstate[3]_i_1_n_0 ),
        .Q(s_axi_CRTLS_BVALID),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    auto_restart_status_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(p_3_in[7]),
        .Q(auto_restart_status_reg_n_0),
        .R(ap_rst_n_inv));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[0]_i_1 
       (.I0(s_axi_CRTLS_WDATA[0]),
        .I1(s_axi_CRTLS_WSTRB[0]),
        .I2(a[0]),
        .O(int_a0[0]));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[10]_i_1 
       (.I0(s_axi_CRTLS_WDATA[10]),
        .I1(s_axi_CRTLS_WSTRB[1]),
        .I2(a[10]),
        .O(int_a0[10]));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[11]_i_1 
       (.I0(s_axi_CRTLS_WDATA[11]),
        .I1(s_axi_CRTLS_WSTRB[1]),
        .I2(a[11]),
        .O(int_a0[11]));
  (* SOFT_HLUTNM = "soft_lutpair18" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[12]_i_1 
       (.I0(s_axi_CRTLS_WDATA[12]),
        .I1(s_axi_CRTLS_WSTRB[1]),
        .I2(a[12]),
        .O(int_a0[12]));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[13]_i_1 
       (.I0(s_axi_CRTLS_WDATA[13]),
        .I1(s_axi_CRTLS_WSTRB[1]),
        .I2(a[13]),
        .O(int_a0[13]));
  (* SOFT_HLUTNM = "soft_lutpair20" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[14]_i_1 
       (.I0(s_axi_CRTLS_WDATA[14]),
        .I1(s_axi_CRTLS_WSTRB[1]),
        .I2(a[14]),
        .O(int_a0[14]));
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[15]_i_1 
       (.I0(s_axi_CRTLS_WDATA[15]),
        .I1(s_axi_CRTLS_WSTRB[1]),
        .I2(a[15]),
        .O(int_a0[15]));
  (* SOFT_HLUTNM = "soft_lutpair23" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[16]_i_1 
       (.I0(s_axi_CRTLS_WDATA[16]),
        .I1(s_axi_CRTLS_WSTRB[2]),
        .I2(a[16]),
        .O(int_a0[16]));
  (* SOFT_HLUTNM = "soft_lutpair23" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[17]_i_1 
       (.I0(s_axi_CRTLS_WDATA[17]),
        .I1(s_axi_CRTLS_WSTRB[2]),
        .I2(a[17]),
        .O(int_a0[17]));
  (* SOFT_HLUTNM = "soft_lutpair25" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[18]_i_1 
       (.I0(s_axi_CRTLS_WDATA[18]),
        .I1(s_axi_CRTLS_WSTRB[2]),
        .I2(a[18]),
        .O(int_a0[18]));
  (* SOFT_HLUTNM = "soft_lutpair25" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[19]_i_1 
       (.I0(s_axi_CRTLS_WDATA[19]),
        .I1(s_axi_CRTLS_WSTRB[2]),
        .I2(a[19]),
        .O(int_a0[19]));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[1]_i_1 
       (.I0(s_axi_CRTLS_WDATA[1]),
        .I1(s_axi_CRTLS_WSTRB[0]),
        .I2(a[1]),
        .O(int_a0[1]));
  (* SOFT_HLUTNM = "soft_lutpair27" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[20]_i_1 
       (.I0(s_axi_CRTLS_WDATA[20]),
        .I1(s_axi_CRTLS_WSTRB[2]),
        .I2(a[20]),
        .O(int_a0[20]));
  (* SOFT_HLUTNM = "soft_lutpair27" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[21]_i_1 
       (.I0(s_axi_CRTLS_WDATA[21]),
        .I1(s_axi_CRTLS_WSTRB[2]),
        .I2(a[21]),
        .O(int_a0[21]));
  (* SOFT_HLUTNM = "soft_lutpair29" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[22]_i_1 
       (.I0(s_axi_CRTLS_WDATA[22]),
        .I1(s_axi_CRTLS_WSTRB[2]),
        .I2(a[22]),
        .O(int_a0[22]));
  (* SOFT_HLUTNM = "soft_lutpair29" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[23]_i_1 
       (.I0(s_axi_CRTLS_WDATA[23]),
        .I1(s_axi_CRTLS_WSTRB[2]),
        .I2(a[23]),
        .O(int_a0[23]));
  (* SOFT_HLUTNM = "soft_lutpair31" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[24]_i_1 
       (.I0(s_axi_CRTLS_WDATA[24]),
        .I1(s_axi_CRTLS_WSTRB[3]),
        .I2(a[24]),
        .O(int_a0[24]));
  (* SOFT_HLUTNM = "soft_lutpair31" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[25]_i_1 
       (.I0(s_axi_CRTLS_WDATA[25]),
        .I1(s_axi_CRTLS_WSTRB[3]),
        .I2(a[25]),
        .O(int_a0[25]));
  (* SOFT_HLUTNM = "soft_lutpair33" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[26]_i_1 
       (.I0(s_axi_CRTLS_WDATA[26]),
        .I1(s_axi_CRTLS_WSTRB[3]),
        .I2(a[26]),
        .O(int_a0[26]));
  (* SOFT_HLUTNM = "soft_lutpair33" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[27]_i_1 
       (.I0(s_axi_CRTLS_WDATA[27]),
        .I1(s_axi_CRTLS_WSTRB[3]),
        .I2(a[27]),
        .O(int_a0[27]));
  (* SOFT_HLUTNM = "soft_lutpair35" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[28]_i_1 
       (.I0(s_axi_CRTLS_WDATA[28]),
        .I1(s_axi_CRTLS_WSTRB[3]),
        .I2(a[28]),
        .O(int_a0[28]));
  (* SOFT_HLUTNM = "soft_lutpair35" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[29]_i_1 
       (.I0(s_axi_CRTLS_WDATA[29]),
        .I1(s_axi_CRTLS_WSTRB[3]),
        .I2(a[29]),
        .O(int_a0[29]));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[2]_i_1 
       (.I0(s_axi_CRTLS_WDATA[2]),
        .I1(s_axi_CRTLS_WSTRB[0]),
        .I2(a[2]),
        .O(int_a0[2]));
  (* SOFT_HLUTNM = "soft_lutpair37" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[30]_i_1 
       (.I0(s_axi_CRTLS_WDATA[30]),
        .I1(s_axi_CRTLS_WSTRB[3]),
        .I2(a[30]),
        .O(int_a0[30]));
  LUT4 #(
    .INIT(16'h0800)) 
    \int_a[31]_i_1 
       (.I0(\waddr_reg_n_0_[4] ),
        .I1(\waddr_reg_n_0_[3] ),
        .I2(\waddr_reg_n_0_[2] ),
        .I3(\int_a[31]_i_3_n_0 ),
        .O(p_0_in));
  (* SOFT_HLUTNM = "soft_lutpair37" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[31]_i_2 
       (.I0(s_axi_CRTLS_WDATA[31]),
        .I1(s_axi_CRTLS_WSTRB[3]),
        .I2(a[31]),
        .O(int_a0[31]));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h01000000)) 
    \int_a[31]_i_3 
       (.I0(\waddr_reg_n_0_[5] ),
        .I1(\waddr_reg_n_0_[1] ),
        .I2(\waddr_reg_n_0_[0] ),
        .I3(\FSM_onehot_wstate_reg[2]_0 ),
        .I4(s_axi_CRTLS_WVALID),
        .O(\int_a[31]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[3]_i_1 
       (.I0(s_axi_CRTLS_WDATA[3]),
        .I1(s_axi_CRTLS_WSTRB[0]),
        .I2(a[3]),
        .O(int_a0[3]));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[4]_i_1 
       (.I0(s_axi_CRTLS_WDATA[4]),
        .I1(s_axi_CRTLS_WSTRB[0]),
        .I2(a[4]),
        .O(int_a0[4]));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[5]_i_1 
       (.I0(s_axi_CRTLS_WDATA[5]),
        .I1(s_axi_CRTLS_WSTRB[0]),
        .I2(a[5]),
        .O(int_a0[5]));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[6]_i_1 
       (.I0(s_axi_CRTLS_WDATA[6]),
        .I1(s_axi_CRTLS_WSTRB[0]),
        .I2(a[6]),
        .O(int_a0[6]));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[7]_i_1 
       (.I0(s_axi_CRTLS_WDATA[7]),
        .I1(s_axi_CRTLS_WSTRB[0]),
        .I2(a[7]),
        .O(int_a0[7]));
  (* SOFT_HLUTNM = "soft_lutpair16" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[8]_i_1 
       (.I0(s_axi_CRTLS_WDATA[8]),
        .I1(s_axi_CRTLS_WSTRB[1]),
        .I2(a[8]),
        .O(int_a0[8]));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_a[9]_i_1 
       (.I0(s_axi_CRTLS_WDATA[9]),
        .I1(s_axi_CRTLS_WSTRB[1]),
        .I2(a[9]),
        .O(int_a0[9]));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[0] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[0]),
        .Q(a[0]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[10] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[10]),
        .Q(a[10]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[11] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[11]),
        .Q(a[11]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[12] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[12]),
        .Q(a[12]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[13] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[13]),
        .Q(a[13]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[14] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[14]),
        .Q(a[14]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[15] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[15]),
        .Q(a[15]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[16] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[16]),
        .Q(a[16]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[17] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[17]),
        .Q(a[17]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[18] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[18]),
        .Q(a[18]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[19] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[19]),
        .Q(a[19]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[1] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[1]),
        .Q(a[1]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[20] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[20]),
        .Q(a[20]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[21] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[21]),
        .Q(a[21]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[22] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[22]),
        .Q(a[22]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[23] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[23]),
        .Q(a[23]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[24] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[24]),
        .Q(a[24]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[25] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[25]),
        .Q(a[25]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[26] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[26]),
        .Q(a[26]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[27] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[27]),
        .Q(a[27]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[28] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[28]),
        .Q(a[28]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[29] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[29]),
        .Q(a[29]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[2] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[2]),
        .Q(a[2]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[30] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[30]),
        .Q(a[30]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[31] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[31]),
        .Q(a[31]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[3] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[3]),
        .Q(a[3]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[4] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[4]),
        .Q(a[4]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[5] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[5]),
        .Q(a[5]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[6] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[6]),
        .Q(a[6]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[7] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[7]),
        .Q(a[7]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[8] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[8]),
        .Q(a[8]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_a_reg[9] 
       (.C(ap_clk),
        .CE(p_0_in),
        .D(int_a0[9]),
        .Q(a[9]),
        .R(ap_rst_n_inv));
  FDRE int_ap_idle_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(1'b1),
        .Q(p_3_in[2]),
        .R(ap_rst_n_inv));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT4 #(
    .INIT(16'h4F44)) 
    int_ap_ready_i_1
       (.I0(p_3_in[7]),
        .I1(ap_done),
        .I2(int_task_ap_done0__3),
        .I3(int_ap_ready),
        .O(int_ap_ready_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    int_ap_ready_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(int_ap_ready_i_1_n_0),
        .Q(int_ap_ready),
        .R(ap_rst_n_inv));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[11]_i_2 
       (.I0(b[11]),
        .I1(a[11]),
        .O(\int_ap_return[11]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[11]_i_3 
       (.I0(b[10]),
        .I1(a[10]),
        .O(\int_ap_return[11]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[11]_i_4 
       (.I0(b[9]),
        .I1(a[9]),
        .O(\int_ap_return[11]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[11]_i_5 
       (.I0(b[8]),
        .I1(a[8]),
        .O(\int_ap_return[11]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[15]_i_2 
       (.I0(b[15]),
        .I1(a[15]),
        .O(\int_ap_return[15]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[15]_i_3 
       (.I0(b[14]),
        .I1(a[14]),
        .O(\int_ap_return[15]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[15]_i_4 
       (.I0(b[13]),
        .I1(a[13]),
        .O(\int_ap_return[15]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[15]_i_5 
       (.I0(b[12]),
        .I1(a[12]),
        .O(\int_ap_return[15]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[19]_i_2 
       (.I0(b[19]),
        .I1(a[19]),
        .O(\int_ap_return[19]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[19]_i_3 
       (.I0(b[18]),
        .I1(a[18]),
        .O(\int_ap_return[19]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[19]_i_4 
       (.I0(b[17]),
        .I1(a[17]),
        .O(\int_ap_return[19]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[19]_i_5 
       (.I0(b[16]),
        .I1(a[16]),
        .O(\int_ap_return[19]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[23]_i_2 
       (.I0(b[23]),
        .I1(a[23]),
        .O(\int_ap_return[23]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[23]_i_3 
       (.I0(b[22]),
        .I1(a[22]),
        .O(\int_ap_return[23]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[23]_i_4 
       (.I0(b[21]),
        .I1(a[21]),
        .O(\int_ap_return[23]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[23]_i_5 
       (.I0(b[20]),
        .I1(a[20]),
        .O(\int_ap_return[23]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[27]_i_2 
       (.I0(b[27]),
        .I1(a[27]),
        .O(\int_ap_return[27]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[27]_i_3 
       (.I0(b[26]),
        .I1(a[26]),
        .O(\int_ap_return[27]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[27]_i_4 
       (.I0(b[25]),
        .I1(a[25]),
        .O(\int_ap_return[27]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[27]_i_5 
       (.I0(b[24]),
        .I1(a[24]),
        .O(\int_ap_return[27]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[31]_i_2 
       (.I0(b[31]),
        .I1(a[31]),
        .O(\int_ap_return[31]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[31]_i_3 
       (.I0(b[30]),
        .I1(a[30]),
        .O(\int_ap_return[31]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[31]_i_4 
       (.I0(b[29]),
        .I1(a[29]),
        .O(\int_ap_return[31]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[31]_i_5 
       (.I0(b[28]),
        .I1(a[28]),
        .O(\int_ap_return[31]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[3]_i_2 
       (.I0(b[3]),
        .I1(a[3]),
        .O(\int_ap_return[3]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[3]_i_3 
       (.I0(b[2]),
        .I1(a[2]),
        .O(\int_ap_return[3]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[3]_i_4 
       (.I0(b[1]),
        .I1(a[1]),
        .O(\int_ap_return[3]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[3]_i_5 
       (.I0(b[0]),
        .I1(a[0]),
        .O(\int_ap_return[3]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[7]_i_2 
       (.I0(b[7]),
        .I1(a[7]),
        .O(\int_ap_return[7]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[7]_i_3 
       (.I0(b[6]),
        .I1(a[6]),
        .O(\int_ap_return[7]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[7]_i_4 
       (.I0(b[5]),
        .I1(a[5]),
        .O(\int_ap_return[7]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \int_ap_return[7]_i_5 
       (.I0(b[4]),
        .I1(a[4]),
        .O(\int_ap_return[7]_i_5_n_0 ));
  FDRE \int_ap_return_reg[0] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[0]),
        .Q(int_ap_return[0]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[10] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[10]),
        .Q(int_ap_return[10]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[11] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[11]),
        .Q(int_ap_return[11]),
        .R(ap_rst_n_inv));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY4 \int_ap_return_reg[11]_i_1 
       (.CI(\int_ap_return_reg[7]_i_1_n_0 ),
        .CO({\int_ap_return_reg[11]_i_1_n_0 ,\int_ap_return_reg[11]_i_1_n_1 ,\int_ap_return_reg[11]_i_1_n_2 ,\int_ap_return_reg[11]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI(b[11:8]),
        .O(ap_return[11:8]),
        .S({\int_ap_return[11]_i_2_n_0 ,\int_ap_return[11]_i_3_n_0 ,\int_ap_return[11]_i_4_n_0 ,\int_ap_return[11]_i_5_n_0 }));
  FDRE \int_ap_return_reg[12] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[12]),
        .Q(int_ap_return[12]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[13] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[13]),
        .Q(int_ap_return[13]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[14] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[14]),
        .Q(int_ap_return[14]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[15] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[15]),
        .Q(int_ap_return[15]),
        .R(ap_rst_n_inv));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY4 \int_ap_return_reg[15]_i_1 
       (.CI(\int_ap_return_reg[11]_i_1_n_0 ),
        .CO({\int_ap_return_reg[15]_i_1_n_0 ,\int_ap_return_reg[15]_i_1_n_1 ,\int_ap_return_reg[15]_i_1_n_2 ,\int_ap_return_reg[15]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI(b[15:12]),
        .O(ap_return[15:12]),
        .S({\int_ap_return[15]_i_2_n_0 ,\int_ap_return[15]_i_3_n_0 ,\int_ap_return[15]_i_4_n_0 ,\int_ap_return[15]_i_5_n_0 }));
  FDRE \int_ap_return_reg[16] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[16]),
        .Q(int_ap_return[16]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[17] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[17]),
        .Q(int_ap_return[17]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[18] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[18]),
        .Q(int_ap_return[18]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[19] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[19]),
        .Q(int_ap_return[19]),
        .R(ap_rst_n_inv));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY4 \int_ap_return_reg[19]_i_1 
       (.CI(\int_ap_return_reg[15]_i_1_n_0 ),
        .CO({\int_ap_return_reg[19]_i_1_n_0 ,\int_ap_return_reg[19]_i_1_n_1 ,\int_ap_return_reg[19]_i_1_n_2 ,\int_ap_return_reg[19]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI(b[19:16]),
        .O(ap_return[19:16]),
        .S({\int_ap_return[19]_i_2_n_0 ,\int_ap_return[19]_i_3_n_0 ,\int_ap_return[19]_i_4_n_0 ,\int_ap_return[19]_i_5_n_0 }));
  FDRE \int_ap_return_reg[1] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[1]),
        .Q(int_ap_return[1]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[20] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[20]),
        .Q(int_ap_return[20]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[21] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[21]),
        .Q(int_ap_return[21]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[22] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[22]),
        .Q(int_ap_return[22]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[23] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[23]),
        .Q(int_ap_return[23]),
        .R(ap_rst_n_inv));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY4 \int_ap_return_reg[23]_i_1 
       (.CI(\int_ap_return_reg[19]_i_1_n_0 ),
        .CO({\int_ap_return_reg[23]_i_1_n_0 ,\int_ap_return_reg[23]_i_1_n_1 ,\int_ap_return_reg[23]_i_1_n_2 ,\int_ap_return_reg[23]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI(b[23:20]),
        .O(ap_return[23:20]),
        .S({\int_ap_return[23]_i_2_n_0 ,\int_ap_return[23]_i_3_n_0 ,\int_ap_return[23]_i_4_n_0 ,\int_ap_return[23]_i_5_n_0 }));
  FDRE \int_ap_return_reg[24] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[24]),
        .Q(int_ap_return[24]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[25] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[25]),
        .Q(int_ap_return[25]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[26] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[26]),
        .Q(int_ap_return[26]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[27] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[27]),
        .Q(int_ap_return[27]),
        .R(ap_rst_n_inv));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY4 \int_ap_return_reg[27]_i_1 
       (.CI(\int_ap_return_reg[23]_i_1_n_0 ),
        .CO({\int_ap_return_reg[27]_i_1_n_0 ,\int_ap_return_reg[27]_i_1_n_1 ,\int_ap_return_reg[27]_i_1_n_2 ,\int_ap_return_reg[27]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI(b[27:24]),
        .O(ap_return[27:24]),
        .S({\int_ap_return[27]_i_2_n_0 ,\int_ap_return[27]_i_3_n_0 ,\int_ap_return[27]_i_4_n_0 ,\int_ap_return[27]_i_5_n_0 }));
  FDRE \int_ap_return_reg[28] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[28]),
        .Q(int_ap_return[28]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[29] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[29]),
        .Q(int_ap_return[29]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[2] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[2]),
        .Q(int_ap_return[2]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[30] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[30]),
        .Q(int_ap_return[30]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[31] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[31]),
        .Q(int_ap_return[31]),
        .R(ap_rst_n_inv));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY4 \int_ap_return_reg[31]_i_1 
       (.CI(\int_ap_return_reg[27]_i_1_n_0 ),
        .CO({\NLW_int_ap_return_reg[31]_i_1_CO_UNCONNECTED [3],\int_ap_return_reg[31]_i_1_n_1 ,\int_ap_return_reg[31]_i_1_n_2 ,\int_ap_return_reg[31]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,b[30:28]}),
        .O(ap_return[31:28]),
        .S({\int_ap_return[31]_i_2_n_0 ,\int_ap_return[31]_i_3_n_0 ,\int_ap_return[31]_i_4_n_0 ,\int_ap_return[31]_i_5_n_0 }));
  FDRE \int_ap_return_reg[3] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[3]),
        .Q(int_ap_return[3]),
        .R(ap_rst_n_inv));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY4 \int_ap_return_reg[3]_i_1 
       (.CI(1'b0),
        .CO({\int_ap_return_reg[3]_i_1_n_0 ,\int_ap_return_reg[3]_i_1_n_1 ,\int_ap_return_reg[3]_i_1_n_2 ,\int_ap_return_reg[3]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI(b[3:0]),
        .O(ap_return[3:0]),
        .S({\int_ap_return[3]_i_2_n_0 ,\int_ap_return[3]_i_3_n_0 ,\int_ap_return[3]_i_4_n_0 ,\int_ap_return[3]_i_5_n_0 }));
  FDRE \int_ap_return_reg[4] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[4]),
        .Q(int_ap_return[4]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[5] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[5]),
        .Q(int_ap_return[5]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[6] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[6]),
        .Q(int_ap_return[6]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[7] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[7]),
        .Q(int_ap_return[7]),
        .R(ap_rst_n_inv));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY4 \int_ap_return_reg[7]_i_1 
       (.CI(\int_ap_return_reg[3]_i_1_n_0 ),
        .CO({\int_ap_return_reg[7]_i_1_n_0 ,\int_ap_return_reg[7]_i_1_n_1 ,\int_ap_return_reg[7]_i_1_n_2 ,\int_ap_return_reg[7]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI(b[7:4]),
        .O(ap_return[7:4]),
        .S({\int_ap_return[7]_i_2_n_0 ,\int_ap_return[7]_i_3_n_0 ,\int_ap_return[7]_i_4_n_0 ,\int_ap_return[7]_i_5_n_0 }));
  FDRE \int_ap_return_reg[8] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[8]),
        .Q(int_ap_return[8]),
        .R(ap_rst_n_inv));
  FDRE \int_ap_return_reg[9] 
       (.C(ap_clk),
        .CE(ap_done),
        .D(ap_return[9]),
        .Q(int_ap_return[9]),
        .R(ap_rst_n_inv));
  LUT4 #(
    .INIT(16'hF888)) 
    int_ap_start_i_1
       (.I0(ap_done),
        .I1(p_3_in[7]),
        .I2(int_ap_start1),
        .I3(s_axi_CRTLS_WDATA[0]),
        .O(int_ap_start_i_1_n_0));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT4 #(
    .INIT(16'h0400)) 
    int_ap_start_i_2
       (.I0(\waddr_reg_n_0_[2] ),
        .I1(int_auto_restart_i_2_n_0),
        .I2(\waddr_reg_n_0_[3] ),
        .I3(s_axi_CRTLS_WSTRB[0]),
        .O(int_ap_start1));
  FDRE #(
    .INIT(1'b0)) 
    int_ap_start_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(int_ap_start_i_1_n_0),
        .Q(ap_done),
        .R(ap_rst_n_inv));
  LUT6 #(
    .INIT(64'hFFEFFFFF00200000)) 
    int_auto_restart_i_1
       (.I0(s_axi_CRTLS_WDATA[7]),
        .I1(\waddr_reg_n_0_[2] ),
        .I2(int_auto_restart_i_2_n_0),
        .I3(\waddr_reg_n_0_[3] ),
        .I4(s_axi_CRTLS_WSTRB[0]),
        .I5(p_3_in[7]),
        .O(int_auto_restart_i_1_n_0));
  LUT6 #(
    .INIT(64'h0000000000000008)) 
    int_auto_restart_i_2
       (.I0(s_axi_CRTLS_WVALID),
        .I1(\FSM_onehot_wstate_reg[2]_0 ),
        .I2(\waddr_reg_n_0_[0] ),
        .I3(\waddr_reg_n_0_[1] ),
        .I4(\waddr_reg_n_0_[5] ),
        .I5(\waddr_reg_n_0_[4] ),
        .O(int_auto_restart_i_2_n_0));
  FDRE #(
    .INIT(1'b0)) 
    int_auto_restart_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(int_auto_restart_i_1_n_0),
        .Q(p_3_in[7]),
        .R(ap_rst_n_inv));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[0]_i_1 
       (.I0(s_axi_CRTLS_WDATA[0]),
        .I1(s_axi_CRTLS_WSTRB[0]),
        .I2(b[0]),
        .O(int_b0[0]));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[10]_i_1 
       (.I0(s_axi_CRTLS_WDATA[10]),
        .I1(s_axi_CRTLS_WSTRB[1]),
        .I2(b[10]),
        .O(int_b0[10]));
  (* SOFT_HLUTNM = "soft_lutpair17" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[11]_i_1 
       (.I0(s_axi_CRTLS_WDATA[11]),
        .I1(s_axi_CRTLS_WSTRB[1]),
        .I2(b[11]),
        .O(int_b0[11]));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[12]_i_1 
       (.I0(s_axi_CRTLS_WDATA[12]),
        .I1(s_axi_CRTLS_WSTRB[1]),
        .I2(b[12]),
        .O(int_b0[12]));
  (* SOFT_HLUTNM = "soft_lutpair19" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[13]_i_1 
       (.I0(s_axi_CRTLS_WDATA[13]),
        .I1(s_axi_CRTLS_WSTRB[1]),
        .I2(b[13]),
        .O(int_b0[13]));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[14]_i_1 
       (.I0(s_axi_CRTLS_WDATA[14]),
        .I1(s_axi_CRTLS_WSTRB[1]),
        .I2(b[14]),
        .O(int_b0[14]));
  (* SOFT_HLUTNM = "soft_lutpair21" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[15]_i_1 
       (.I0(s_axi_CRTLS_WDATA[15]),
        .I1(s_axi_CRTLS_WSTRB[1]),
        .I2(b[15]),
        .O(int_b0[15]));
  (* SOFT_HLUTNM = "soft_lutpair22" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[16]_i_1 
       (.I0(s_axi_CRTLS_WDATA[16]),
        .I1(s_axi_CRTLS_WSTRB[2]),
        .I2(b[16]),
        .O(int_b0[16]));
  (* SOFT_HLUTNM = "soft_lutpair22" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[17]_i_1 
       (.I0(s_axi_CRTLS_WDATA[17]),
        .I1(s_axi_CRTLS_WSTRB[2]),
        .I2(b[17]),
        .O(int_b0[17]));
  (* SOFT_HLUTNM = "soft_lutpair24" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[18]_i_1 
       (.I0(s_axi_CRTLS_WDATA[18]),
        .I1(s_axi_CRTLS_WSTRB[2]),
        .I2(b[18]),
        .O(int_b0[18]));
  (* SOFT_HLUTNM = "soft_lutpair24" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[19]_i_1 
       (.I0(s_axi_CRTLS_WDATA[19]),
        .I1(s_axi_CRTLS_WSTRB[2]),
        .I2(b[19]),
        .O(int_b0[19]));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[1]_i_1 
       (.I0(s_axi_CRTLS_WDATA[1]),
        .I1(s_axi_CRTLS_WSTRB[0]),
        .I2(b[1]),
        .O(int_b0[1]));
  (* SOFT_HLUTNM = "soft_lutpair26" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[20]_i_1 
       (.I0(s_axi_CRTLS_WDATA[20]),
        .I1(s_axi_CRTLS_WSTRB[2]),
        .I2(b[20]),
        .O(int_b0[20]));
  (* SOFT_HLUTNM = "soft_lutpair26" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[21]_i_1 
       (.I0(s_axi_CRTLS_WDATA[21]),
        .I1(s_axi_CRTLS_WSTRB[2]),
        .I2(b[21]),
        .O(int_b0[21]));
  (* SOFT_HLUTNM = "soft_lutpair28" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[22]_i_1 
       (.I0(s_axi_CRTLS_WDATA[22]),
        .I1(s_axi_CRTLS_WSTRB[2]),
        .I2(b[22]),
        .O(int_b0[22]));
  (* SOFT_HLUTNM = "soft_lutpair28" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[23]_i_1 
       (.I0(s_axi_CRTLS_WDATA[23]),
        .I1(s_axi_CRTLS_WSTRB[2]),
        .I2(b[23]),
        .O(int_b0[23]));
  (* SOFT_HLUTNM = "soft_lutpair30" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[24]_i_1 
       (.I0(s_axi_CRTLS_WDATA[24]),
        .I1(s_axi_CRTLS_WSTRB[3]),
        .I2(b[24]),
        .O(int_b0[24]));
  (* SOFT_HLUTNM = "soft_lutpair30" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[25]_i_1 
       (.I0(s_axi_CRTLS_WDATA[25]),
        .I1(s_axi_CRTLS_WSTRB[3]),
        .I2(b[25]),
        .O(int_b0[25]));
  (* SOFT_HLUTNM = "soft_lutpair32" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[26]_i_1 
       (.I0(s_axi_CRTLS_WDATA[26]),
        .I1(s_axi_CRTLS_WSTRB[3]),
        .I2(b[26]),
        .O(int_b0[26]));
  (* SOFT_HLUTNM = "soft_lutpair32" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[27]_i_1 
       (.I0(s_axi_CRTLS_WDATA[27]),
        .I1(s_axi_CRTLS_WSTRB[3]),
        .I2(b[27]),
        .O(int_b0[27]));
  (* SOFT_HLUTNM = "soft_lutpair34" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[28]_i_1 
       (.I0(s_axi_CRTLS_WDATA[28]),
        .I1(s_axi_CRTLS_WSTRB[3]),
        .I2(b[28]),
        .O(int_b0[28]));
  (* SOFT_HLUTNM = "soft_lutpair34" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[29]_i_1 
       (.I0(s_axi_CRTLS_WDATA[29]),
        .I1(s_axi_CRTLS_WSTRB[3]),
        .I2(b[29]),
        .O(int_b0[29]));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[2]_i_1 
       (.I0(s_axi_CRTLS_WDATA[2]),
        .I1(s_axi_CRTLS_WSTRB[0]),
        .I2(b[2]),
        .O(int_b0[2]));
  (* SOFT_HLUTNM = "soft_lutpair36" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[30]_i_1 
       (.I0(s_axi_CRTLS_WDATA[30]),
        .I1(s_axi_CRTLS_WSTRB[3]),
        .I2(b[30]),
        .O(int_b0[30]));
  LUT5 #(
    .INIT(32'h00000002)) 
    \int_b[31]_i_1 
       (.I0(\waddr_reg_n_0_[5] ),
        .I1(\waddr_reg_n_0_[4] ),
        .I2(\int_b[31]_i_3_n_0 ),
        .I3(\waddr_reg_n_0_[2] ),
        .I4(\waddr_reg_n_0_[3] ),
        .O(\int_b[31]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair36" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[31]_i_2 
       (.I0(s_axi_CRTLS_WDATA[31]),
        .I1(s_axi_CRTLS_WSTRB[3]),
        .I2(b[31]),
        .O(int_b0[31]));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT4 #(
    .INIT(16'hFFF7)) 
    \int_b[31]_i_3 
       (.I0(s_axi_CRTLS_WVALID),
        .I1(\FSM_onehot_wstate_reg[2]_0 ),
        .I2(\waddr_reg_n_0_[0] ),
        .I3(\waddr_reg_n_0_[1] ),
        .O(\int_b[31]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[3]_i_1 
       (.I0(s_axi_CRTLS_WDATA[3]),
        .I1(s_axi_CRTLS_WSTRB[0]),
        .I2(b[3]),
        .O(int_b0[3]));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[4]_i_1 
       (.I0(s_axi_CRTLS_WDATA[4]),
        .I1(s_axi_CRTLS_WSTRB[0]),
        .I2(b[4]),
        .O(int_b0[4]));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[5]_i_1 
       (.I0(s_axi_CRTLS_WDATA[5]),
        .I1(s_axi_CRTLS_WSTRB[0]),
        .I2(b[5]),
        .O(int_b0[5]));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[6]_i_1 
       (.I0(s_axi_CRTLS_WDATA[6]),
        .I1(s_axi_CRTLS_WSTRB[0]),
        .I2(b[6]),
        .O(int_b0[6]));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[7]_i_1 
       (.I0(s_axi_CRTLS_WDATA[7]),
        .I1(s_axi_CRTLS_WSTRB[0]),
        .I2(b[7]),
        .O(int_b0[7]));
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[8]_i_1 
       (.I0(s_axi_CRTLS_WDATA[8]),
        .I1(s_axi_CRTLS_WSTRB[1]),
        .I2(b[8]),
        .O(int_b0[8]));
  (* SOFT_HLUTNM = "soft_lutpair15" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \int_b[9]_i_1 
       (.I0(s_axi_CRTLS_WDATA[9]),
        .I1(s_axi_CRTLS_WSTRB[1]),
        .I2(b[9]),
        .O(int_b0[9]));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[0] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[0]),
        .Q(b[0]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[10] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[10]),
        .Q(b[10]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[11] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[11]),
        .Q(b[11]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[12] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[12]),
        .Q(b[12]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[13] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[13]),
        .Q(b[13]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[14] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[14]),
        .Q(b[14]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[15] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[15]),
        .Q(b[15]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[16] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[16]),
        .Q(b[16]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[17] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[17]),
        .Q(b[17]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[18] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[18]),
        .Q(b[18]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[19] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[19]),
        .Q(b[19]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[1] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[1]),
        .Q(b[1]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[20] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[20]),
        .Q(b[20]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[21] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[21]),
        .Q(b[21]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[22] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[22]),
        .Q(b[22]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[23] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[23]),
        .Q(b[23]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[24] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[24]),
        .Q(b[24]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[25] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[25]),
        .Q(b[25]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[26] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[26]),
        .Q(b[26]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[27] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[27]),
        .Q(b[27]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[28] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[28]),
        .Q(b[28]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[29] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[29]),
        .Q(b[29]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[2] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[2]),
        .Q(b[2]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[30] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[30]),
        .Q(b[30]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[31] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[31]),
        .Q(b[31]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[3] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[3]),
        .Q(b[3]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[4] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[4]),
        .Q(b[4]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[5] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[5]),
        .Q(b[5]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[6] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[6]),
        .Q(b[6]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[7] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[7]),
        .Q(b[7]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[8] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[8]),
        .Q(b[8]),
        .R(ap_rst_n_inv));
  FDRE #(
    .INIT(1'b0)) 
    \int_b_reg[9] 
       (.C(ap_clk),
        .CE(\int_b[31]_i_1_n_0 ),
        .D(int_b0[9]),
        .Q(b[9]),
        .R(ap_rst_n_inv));
  LUT6 #(
    .INIT(64'hFFBFFFFF00800000)) 
    int_gie_i_1
       (.I0(s_axi_CRTLS_WDATA[0]),
        .I1(s_axi_CRTLS_WSTRB[0]),
        .I2(int_auto_restart_i_2_n_0),
        .I3(\waddr_reg_n_0_[3] ),
        .I4(\waddr_reg_n_0_[2] ),
        .I5(int_gie_reg_n_0),
        .O(int_gie_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    int_gie_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(int_gie_i_1_n_0),
        .Q(int_gie_reg_n_0),
        .R(ap_rst_n_inv));
  LUT6 #(
    .INIT(64'hFBFFFFFF08000000)) 
    int_ier_i_1
       (.I0(s_axi_CRTLS_WDATA[0]),
        .I1(s_axi_CRTLS_WSTRB[0]),
        .I2(\waddr_reg_n_0_[2] ),
        .I3(\waddr_reg_n_0_[3] ),
        .I4(int_auto_restart_i_2_n_0),
        .I5(int_ier),
        .O(int_ier_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    int_ier_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(int_ier_i_1_n_0),
        .Q(int_ier),
        .R(ap_rst_n_inv));
  LUT2 #(
    .INIT(4'h8)) 
    int_interrupt_i_1
       (.I0(int_gie_reg_n_0),
        .I1(int_interrupt1),
        .O(int_interrupt0));
  FDRE #(
    .INIT(1'b0)) 
    int_interrupt_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(int_interrupt0),
        .Q(interrupt),
        .R(ap_rst_n_inv));
  LUT6 #(
    .INIT(64'hFFFF7FFFFFFF8000)) 
    int_isr_i_1
       (.I0(s_axi_CRTLS_WDATA[0]),
        .I1(\waddr_reg_n_0_[2] ),
        .I2(int_isr_i_2_n_0),
        .I3(s_axi_CRTLS_WSTRB[0]),
        .I4(int_isr6_out),
        .I5(int_interrupt1),
        .O(int_isr_i_1_n_0));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT2 #(
    .INIT(4'h8)) 
    int_isr_i_2
       (.I0(\waddr_reg_n_0_[3] ),
        .I1(int_auto_restart_i_2_n_0),
        .O(int_isr_i_2_n_0));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT2 #(
    .INIT(4'h8)) 
    int_isr_i_3
       (.I0(ap_done),
        .I1(int_ier),
        .O(int_isr6_out));
  FDRE #(
    .INIT(1'b0)) 
    int_isr_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(int_isr_i_1_n_0),
        .Q(int_interrupt1),
        .R(ap_rst_n_inv));
  LUT5 #(
    .INIT(32'h72FF7272)) 
    int_task_ap_done_i_1
       (.I0(auto_restart_status_reg_n_0),
        .I1(p_3_in[2]),
        .I2(ap_done),
        .I3(int_task_ap_done0__3),
        .I4(int_task_ap_done),
        .O(int_task_ap_done_i_1_n_0));
  LUT6 #(
    .INIT(64'h0000000100000000)) 
    int_task_ap_done_i_2
       (.I0(s_axi_CRTLS_ARADDR[2]),
        .I1(s_axi_CRTLS_ARADDR[3]),
        .I2(int_task_ap_done_i_3_n_0),
        .I3(s_axi_CRTLS_ARADDR[4]),
        .I4(s_axi_CRTLS_ARADDR[5]),
        .I5(ar_hs),
        .O(int_task_ap_done0__3));
  LUT2 #(
    .INIT(4'hE)) 
    int_task_ap_done_i_3
       (.I0(s_axi_CRTLS_ARADDR[1]),
        .I1(s_axi_CRTLS_ARADDR[0]),
        .O(int_task_ap_done_i_3_n_0));
  FDRE #(
    .INIT(1'b0)) 
    int_task_ap_done_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(int_task_ap_done_i_1_n_0),
        .Q(int_task_ap_done),
        .R(ap_rst_n_inv));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[0]_i_2 
       (.I0(int_interrupt1),
        .I1(int_ier),
        .I2(\rdata[31]_i_4_n_0 ),
        .I3(int_gie_reg_n_0),
        .I4(\rdata[31]_i_5_n_0 ),
        .I5(ap_done),
        .O(\rdata[0]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[0]_i_3 
       (.I0(b[0]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[0]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[0]),
        .O(\rdata[0]_i_3_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[10]_i_1 
       (.I0(b[10]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[10]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[10]),
        .O(\rdata[10]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[11]_i_1 
       (.I0(b[11]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[11]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[11]),
        .O(\rdata[11]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[12]_i_1 
       (.I0(b[12]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[12]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[12]),
        .O(\rdata[12]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[13]_i_1 
       (.I0(b[13]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[13]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[13]),
        .O(\rdata[13]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[14]_i_1 
       (.I0(b[14]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[14]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[14]),
        .O(\rdata[14]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[15]_i_1 
       (.I0(b[15]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[15]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[15]),
        .O(\rdata[15]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[16]_i_1 
       (.I0(b[16]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[16]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[16]),
        .O(\rdata[16]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[17]_i_1 
       (.I0(b[17]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[17]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[17]),
        .O(\rdata[17]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[18]_i_1 
       (.I0(b[18]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[18]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[18]),
        .O(\rdata[18]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[19]_i_1 
       (.I0(b[19]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[19]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[19]),
        .O(\rdata[19]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h00A000A0C0CFC0C0)) 
    \rdata[1]_i_1 
       (.I0(b[1]),
        .I1(\rdata[1]_i_2_n_0 ),
        .I2(\rdata[9]_i_3_n_0 ),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_task_ap_done),
        .I5(\rdata[31]_i_4_n_0 ),
        .O(rdata[1]));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \rdata[1]_i_2 
       (.I0(a[1]),
        .I1(\rdata[31]_i_5_n_0 ),
        .I2(int_ap_return[1]),
        .O(\rdata[1]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[20]_i_1 
       (.I0(b[20]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[20]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[20]),
        .O(\rdata[20]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[21]_i_1 
       (.I0(b[21]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[21]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[21]),
        .O(\rdata[21]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[22]_i_1 
       (.I0(b[22]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[22]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[22]),
        .O(\rdata[22]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[23]_i_1 
       (.I0(b[23]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[23]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[23]),
        .O(\rdata[23]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[24]_i_1 
       (.I0(b[24]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[24]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[24]),
        .O(\rdata[24]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[25]_i_1 
       (.I0(b[25]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[25]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[25]),
        .O(\rdata[25]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[26]_i_1 
       (.I0(b[26]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[26]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[26]),
        .O(\rdata[26]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[27]_i_1 
       (.I0(b[27]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[27]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[27]),
        .O(\rdata[27]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[28]_i_1 
       (.I0(b[28]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[28]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[28]),
        .O(\rdata[28]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[29]_i_1 
       (.I0(b[29]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[29]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[29]),
        .O(\rdata[29]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h00A000A0C0CFC0C0)) 
    \rdata[2]_i_1 
       (.I0(b[2]),
        .I1(\rdata[2]_i_2_n_0 ),
        .I2(\rdata[9]_i_3_n_0 ),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(p_3_in[2]),
        .I5(\rdata[31]_i_4_n_0 ),
        .O(rdata[2]));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \rdata[2]_i_2 
       (.I0(a[2]),
        .I1(\rdata[31]_i_5_n_0 ),
        .I2(int_ap_return[2]),
        .O(\rdata[2]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[30]_i_1 
       (.I0(b[30]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[30]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[30]),
        .O(\rdata[30]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0000000000000008)) 
    \rdata[31]_i_1 
       (.I0(s_axi_CRTLS_ARVALID),
        .I1(\FSM_onehot_rstate_reg[1]_0 ),
        .I2(s_axi_CRTLS_ARADDR[1]),
        .I3(s_axi_CRTLS_ARADDR[0]),
        .I4(s_axi_CRTLS_ARADDR[4]),
        .I5(s_axi_CRTLS_ARADDR[5]),
        .O(\rdata[31]_i_1_n_0 ));
  LUT2 #(
    .INIT(4'h8)) 
    \rdata[31]_i_2 
       (.I0(\FSM_onehot_rstate_reg[1]_0 ),
        .I1(s_axi_CRTLS_ARVALID),
        .O(ar_hs));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[31]_i_3 
       (.I0(b[31]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[31]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[31]),
        .O(\rdata[31]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFEFEFEFFFE)) 
    \rdata[31]_i_4 
       (.I0(s_axi_CRTLS_ARADDR[1]),
        .I1(s_axi_CRTLS_ARADDR[0]),
        .I2(s_axi_CRTLS_ARADDR[5]),
        .I3(s_axi_CRTLS_ARADDR[3]),
        .I4(s_axi_CRTLS_ARADDR[4]),
        .I5(s_axi_CRTLS_ARADDR[2]),
        .O(\rdata[31]_i_4_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFEEA)) 
    \rdata[31]_i_5 
       (.I0(s_axi_CRTLS_ARADDR[1]),
        .I1(s_axi_CRTLS_ARADDR[4]),
        .I2(s_axi_CRTLS_ARADDR[5]),
        .I3(s_axi_CRTLS_ARADDR[3]),
        .I4(s_axi_CRTLS_ARADDR[0]),
        .I5(s_axi_CRTLS_ARADDR[2]),
        .O(\rdata[31]_i_5_n_0 ));
  LUT6 #(
    .INIT(64'h00A000A0C0CFC0C0)) 
    \rdata[3]_i_1 
       (.I0(b[3]),
        .I1(\rdata[3]_i_2_n_0 ),
        .I2(\rdata[9]_i_3_n_0 ),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_ready),
        .I5(\rdata[31]_i_4_n_0 ),
        .O(rdata[3]));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \rdata[3]_i_2 
       (.I0(a[3]),
        .I1(\rdata[31]_i_5_n_0 ),
        .I2(int_ap_return[3]),
        .O(\rdata[3]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[4]_i_1 
       (.I0(b[4]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[4]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[4]),
        .O(\rdata[4]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[5]_i_1 
       (.I0(b[5]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[5]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[5]),
        .O(\rdata[5]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[6]_i_1 
       (.I0(b[6]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[6]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[6]),
        .O(\rdata[6]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h00A000A0C0CFC0C0)) 
    \rdata[7]_i_1 
       (.I0(b[7]),
        .I1(\rdata[7]_i_2_n_0 ),
        .I2(\rdata[9]_i_3_n_0 ),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(p_3_in[7]),
        .I5(\rdata[31]_i_4_n_0 ),
        .O(rdata[7]));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \rdata[7]_i_2 
       (.I0(a[7]),
        .I1(\rdata[31]_i_5_n_0 ),
        .I2(int_ap_return[7]),
        .O(\rdata[7]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h30BB3088)) 
    \rdata[8]_i_1 
       (.I0(b[8]),
        .I1(\rdata[31]_i_4_n_0 ),
        .I2(a[8]),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(int_ap_return[8]),
        .O(\rdata[8]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h00A000A0C0CFC0C0)) 
    \rdata[9]_i_1 
       (.I0(b[9]),
        .I1(\rdata[9]_i_2_n_0 ),
        .I2(\rdata[9]_i_3_n_0 ),
        .I3(\rdata[31]_i_5_n_0 ),
        .I4(interrupt),
        .I5(\rdata[31]_i_4_n_0 ),
        .O(rdata[9]));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    \rdata[9]_i_2 
       (.I0(a[9]),
        .I1(\rdata[31]_i_5_n_0 ),
        .I2(int_ap_return[9]),
        .O(\rdata[9]_i_2_n_0 ));
  LUT4 #(
    .INIT(16'hFFFE)) 
    \rdata[9]_i_3 
       (.I0(s_axi_CRTLS_ARADDR[5]),
        .I1(s_axi_CRTLS_ARADDR[4]),
        .I2(s_axi_CRTLS_ARADDR[0]),
        .I3(s_axi_CRTLS_ARADDR[1]),
        .O(\rdata[9]_i_3_n_0 ));
  FDRE \rdata_reg[0] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(rdata[0]),
        .Q(s_axi_CRTLS_RDATA[0]),
        .R(1'b0));
  MUXF7 \rdata_reg[0]_i_1 
       (.I0(\rdata[0]_i_2_n_0 ),
        .I1(\rdata[0]_i_3_n_0 ),
        .O(rdata[0]),
        .S(\rdata[9]_i_3_n_0 ));
  FDRE \rdata_reg[10] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[10]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[10]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[11] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[11]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[11]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[12] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[12]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[12]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[13] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[13]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[13]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[14] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[14]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[14]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[15] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[15]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[15]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[16] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[16]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[16]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[17] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[17]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[17]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[18] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[18]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[18]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[19] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[19]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[19]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[1] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(rdata[1]),
        .Q(s_axi_CRTLS_RDATA[1]),
        .R(1'b0));
  FDRE \rdata_reg[20] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[20]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[20]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[21] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[21]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[21]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[22] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[22]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[22]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[23] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[23]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[23]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[24] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[24]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[24]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[25] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[25]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[25]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[26] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[26]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[26]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[27] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[27]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[27]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[28] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[28]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[28]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[29] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[29]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[29]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[2] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(rdata[2]),
        .Q(s_axi_CRTLS_RDATA[2]),
        .R(1'b0));
  FDRE \rdata_reg[30] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[30]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[30]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[31] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[31]_i_3_n_0 ),
        .Q(s_axi_CRTLS_RDATA[31]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[3] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(rdata[3]),
        .Q(s_axi_CRTLS_RDATA[3]),
        .R(1'b0));
  FDRE \rdata_reg[4] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[4]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[4]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[5] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[5]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[5]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[6] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[6]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[6]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[7] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(rdata[7]),
        .Q(s_axi_CRTLS_RDATA[7]),
        .R(1'b0));
  FDRE \rdata_reg[8] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(\rdata[8]_i_1_n_0 ),
        .Q(s_axi_CRTLS_RDATA[8]),
        .R(\rdata[31]_i_1_n_0 ));
  FDRE \rdata_reg[9] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(rdata[9]),
        .Q(s_axi_CRTLS_RDATA[9]),
        .R(1'b0));
  LUT2 #(
    .INIT(4'h8)) 
    \waddr[5]_i_1 
       (.I0(\FSM_onehot_wstate_reg[1]_0 ),
        .I1(s_axi_CRTLS_AWVALID),
        .O(waddr));
  FDRE \waddr_reg[0] 
       (.C(ap_clk),
        .CE(waddr),
        .D(s_axi_CRTLS_AWADDR[0]),
        .Q(\waddr_reg_n_0_[0] ),
        .R(1'b0));
  FDRE \waddr_reg[1] 
       (.C(ap_clk),
        .CE(waddr),
        .D(s_axi_CRTLS_AWADDR[1]),
        .Q(\waddr_reg_n_0_[1] ),
        .R(1'b0));
  FDRE \waddr_reg[2] 
       (.C(ap_clk),
        .CE(waddr),
        .D(s_axi_CRTLS_AWADDR[2]),
        .Q(\waddr_reg_n_0_[2] ),
        .R(1'b0));
  FDRE \waddr_reg[3] 
       (.C(ap_clk),
        .CE(waddr),
        .D(s_axi_CRTLS_AWADDR[3]),
        .Q(\waddr_reg_n_0_[3] ),
        .R(1'b0));
  FDRE \waddr_reg[4] 
       (.C(ap_clk),
        .CE(waddr),
        .D(s_axi_CRTLS_AWADDR[4]),
        .Q(\waddr_reg_n_0_[4] ),
        .R(1'b0));
  FDRE \waddr_reg[5] 
       (.C(ap_clk),
        .CE(waddr),
        .D(s_axi_CRTLS_AWADDR[5]),
        .Q(\waddr_reg_n_0_[5] ),
        .R(1'b0));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;
    parameter GRES_WIDTH = 10000;
    parameter GRES_START = 10000;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    wire GRESTORE;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;
    reg GRESTORE_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;
    assign (strong1, weak0) GRESTORE = GRESTORE_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

    initial begin 
	GRESTORE_int = 1'b0;
	#(GRES_START);
	GRESTORE_int = 1'b1;
	#(GRES_WIDTH);
	GRESTORE_int = 1'b0;
    end

endmodule
`endif
