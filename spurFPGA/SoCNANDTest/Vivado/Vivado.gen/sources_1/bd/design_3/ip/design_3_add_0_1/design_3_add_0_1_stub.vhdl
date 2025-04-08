-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2023.2 (win64) Build 4029153 Fri Oct 13 20:14:34 MDT 2023
-- Date        : Wed Jul 17 12:15:43 2024
-- Host        : gerard running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/Research/CU-Spur-Sean/spurFPGA/SoCNANDTest/Vivado/Vivado.gen/sources_1/bd/design_3/ip/design_3_add_0_1/design_3_add_0_1_stub.vhdl
-- Design      : design_3_add_0_1
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7z007sclg400-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity design_3_add_0_1 is
  Port ( 
    s_axi_CRTLS_AWADDR : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s_axi_CRTLS_AWVALID : in STD_LOGIC;
    s_axi_CRTLS_AWREADY : out STD_LOGIC;
    s_axi_CRTLS_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_CRTLS_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_CRTLS_WVALID : in STD_LOGIC;
    s_axi_CRTLS_WREADY : out STD_LOGIC;
    s_axi_CRTLS_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_CRTLS_BVALID : out STD_LOGIC;
    s_axi_CRTLS_BREADY : in STD_LOGIC;
    s_axi_CRTLS_ARADDR : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s_axi_CRTLS_ARVALID : in STD_LOGIC;
    s_axi_CRTLS_ARREADY : out STD_LOGIC;
    s_axi_CRTLS_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_CRTLS_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_CRTLS_RVALID : out STD_LOGIC;
    s_axi_CRTLS_RREADY : in STD_LOGIC;
    ap_clk : in STD_LOGIC;
    ap_rst_n : in STD_LOGIC;
    interrupt : out STD_LOGIC
  );

end design_3_add_0_1;

architecture stub of design_3_add_0_1 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "s_axi_CRTLS_AWADDR[5:0],s_axi_CRTLS_AWVALID,s_axi_CRTLS_AWREADY,s_axi_CRTLS_WDATA[31:0],s_axi_CRTLS_WSTRB[3:0],s_axi_CRTLS_WVALID,s_axi_CRTLS_WREADY,s_axi_CRTLS_BRESP[1:0],s_axi_CRTLS_BVALID,s_axi_CRTLS_BREADY,s_axi_CRTLS_ARADDR[5:0],s_axi_CRTLS_ARVALID,s_axi_CRTLS_ARREADY,s_axi_CRTLS_RDATA[31:0],s_axi_CRTLS_RRESP[1:0],s_axi_CRTLS_RVALID,s_axi_CRTLS_RREADY,ap_clk,ap_rst_n,interrupt";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "add,Vivado 2023.2";
begin
end;
