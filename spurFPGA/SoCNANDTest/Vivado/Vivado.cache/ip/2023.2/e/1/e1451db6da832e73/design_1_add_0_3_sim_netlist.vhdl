-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2023.2 (win64) Build 4029153 Fri Oct 13 20:14:34 MDT 2023
-- Date        : Mon Jul 15 17:15:12 2024
-- Host        : gerard running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
--               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ design_1_add_0_3_sim_netlist.vhdl
-- Design      : design_1_add_0_3
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xc7z007sclg400-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_add is
  port (
    ap_start : in STD_LOGIC;
    ap_done : out STD_LOGIC;
    ap_idle : out STD_LOGIC;
    ap_ready : out STD_LOGIC;
    a : in STD_LOGIC_VECTOR ( 31 downto 0 );
    b : in STD_LOGIC_VECTOR ( 31 downto 0 );
    ap_return : out STD_LOGIC_VECTOR ( 31 downto 0 )
  );
  attribute hls_module : string;
  attribute hls_module of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_add : entity is "yes";
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_add;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_add is
  signal \<const0>\ : STD_LOGIC;
  signal \ap_return[0]_INST_0_i_1_n_0\ : STD_LOGIC;
  signal \ap_return[0]_INST_0_i_2_n_0\ : STD_LOGIC;
  signal \ap_return[0]_INST_0_i_3_n_0\ : STD_LOGIC;
  signal \ap_return[0]_INST_0_i_4_n_0\ : STD_LOGIC;
  signal \ap_return[0]_INST_0_n_0\ : STD_LOGIC;
  signal \ap_return[0]_INST_0_n_1\ : STD_LOGIC;
  signal \ap_return[0]_INST_0_n_2\ : STD_LOGIC;
  signal \ap_return[0]_INST_0_n_3\ : STD_LOGIC;
  signal \ap_return[12]_INST_0_i_1_n_0\ : STD_LOGIC;
  signal \ap_return[12]_INST_0_i_2_n_0\ : STD_LOGIC;
  signal \ap_return[12]_INST_0_i_3_n_0\ : STD_LOGIC;
  signal \ap_return[12]_INST_0_i_4_n_0\ : STD_LOGIC;
  signal \ap_return[12]_INST_0_n_0\ : STD_LOGIC;
  signal \ap_return[12]_INST_0_n_1\ : STD_LOGIC;
  signal \ap_return[12]_INST_0_n_2\ : STD_LOGIC;
  signal \ap_return[12]_INST_0_n_3\ : STD_LOGIC;
  signal \ap_return[16]_INST_0_i_1_n_0\ : STD_LOGIC;
  signal \ap_return[16]_INST_0_i_2_n_0\ : STD_LOGIC;
  signal \ap_return[16]_INST_0_i_3_n_0\ : STD_LOGIC;
  signal \ap_return[16]_INST_0_i_4_n_0\ : STD_LOGIC;
  signal \ap_return[16]_INST_0_n_0\ : STD_LOGIC;
  signal \ap_return[16]_INST_0_n_1\ : STD_LOGIC;
  signal \ap_return[16]_INST_0_n_2\ : STD_LOGIC;
  signal \ap_return[16]_INST_0_n_3\ : STD_LOGIC;
  signal \ap_return[20]_INST_0_i_1_n_0\ : STD_LOGIC;
  signal \ap_return[20]_INST_0_i_2_n_0\ : STD_LOGIC;
  signal \ap_return[20]_INST_0_i_3_n_0\ : STD_LOGIC;
  signal \ap_return[20]_INST_0_i_4_n_0\ : STD_LOGIC;
  signal \ap_return[20]_INST_0_n_0\ : STD_LOGIC;
  signal \ap_return[20]_INST_0_n_1\ : STD_LOGIC;
  signal \ap_return[20]_INST_0_n_2\ : STD_LOGIC;
  signal \ap_return[20]_INST_0_n_3\ : STD_LOGIC;
  signal \ap_return[24]_INST_0_i_1_n_0\ : STD_LOGIC;
  signal \ap_return[24]_INST_0_i_2_n_0\ : STD_LOGIC;
  signal \ap_return[24]_INST_0_i_3_n_0\ : STD_LOGIC;
  signal \ap_return[24]_INST_0_i_4_n_0\ : STD_LOGIC;
  signal \ap_return[24]_INST_0_n_0\ : STD_LOGIC;
  signal \ap_return[24]_INST_0_n_1\ : STD_LOGIC;
  signal \ap_return[24]_INST_0_n_2\ : STD_LOGIC;
  signal \ap_return[24]_INST_0_n_3\ : STD_LOGIC;
  signal \ap_return[28]_INST_0_i_1_n_0\ : STD_LOGIC;
  signal \ap_return[28]_INST_0_i_2_n_0\ : STD_LOGIC;
  signal \ap_return[28]_INST_0_i_3_n_0\ : STD_LOGIC;
  signal \ap_return[28]_INST_0_i_4_n_0\ : STD_LOGIC;
  signal \ap_return[28]_INST_0_n_1\ : STD_LOGIC;
  signal \ap_return[28]_INST_0_n_2\ : STD_LOGIC;
  signal \ap_return[28]_INST_0_n_3\ : STD_LOGIC;
  signal \ap_return[4]_INST_0_i_1_n_0\ : STD_LOGIC;
  signal \ap_return[4]_INST_0_i_2_n_0\ : STD_LOGIC;
  signal \ap_return[4]_INST_0_i_3_n_0\ : STD_LOGIC;
  signal \ap_return[4]_INST_0_i_4_n_0\ : STD_LOGIC;
  signal \ap_return[4]_INST_0_n_0\ : STD_LOGIC;
  signal \ap_return[4]_INST_0_n_1\ : STD_LOGIC;
  signal \ap_return[4]_INST_0_n_2\ : STD_LOGIC;
  signal \ap_return[4]_INST_0_n_3\ : STD_LOGIC;
  signal \ap_return[8]_INST_0_i_1_n_0\ : STD_LOGIC;
  signal \ap_return[8]_INST_0_i_2_n_0\ : STD_LOGIC;
  signal \ap_return[8]_INST_0_i_3_n_0\ : STD_LOGIC;
  signal \ap_return[8]_INST_0_i_4_n_0\ : STD_LOGIC;
  signal \ap_return[8]_INST_0_n_0\ : STD_LOGIC;
  signal \ap_return[8]_INST_0_n_1\ : STD_LOGIC;
  signal \ap_return[8]_INST_0_n_2\ : STD_LOGIC;
  signal \ap_return[8]_INST_0_n_3\ : STD_LOGIC;
  signal \^ap_start\ : STD_LOGIC;
  signal \NLW_ap_return[28]_INST_0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 to 3 );
  attribute ADDER_THRESHOLD : integer;
  attribute ADDER_THRESHOLD of \ap_return[0]_INST_0\ : label is 35;
  attribute ADDER_THRESHOLD of \ap_return[12]_INST_0\ : label is 35;
  attribute ADDER_THRESHOLD of \ap_return[16]_INST_0\ : label is 35;
  attribute ADDER_THRESHOLD of \ap_return[20]_INST_0\ : label is 35;
  attribute ADDER_THRESHOLD of \ap_return[24]_INST_0\ : label is 35;
  attribute ADDER_THRESHOLD of \ap_return[28]_INST_0\ : label is 35;
  attribute ADDER_THRESHOLD of \ap_return[4]_INST_0\ : label is 35;
  attribute ADDER_THRESHOLD of \ap_return[8]_INST_0\ : label is 35;
begin
  \^ap_start\ <= ap_start;
  ap_done <= \^ap_start\;
  ap_idle <= \<const0>\;
  ap_ready <= \^ap_start\;
GND: unisim.vcomponents.GND
     port map (
      G => \<const0>\
    );
\ap_return[0]_INST_0\: unisim.vcomponents.CARRY4
     port map (
      CI => '0',
      CO(3) => \ap_return[0]_INST_0_n_0\,
      CO(2) => \ap_return[0]_INST_0_n_1\,
      CO(1) => \ap_return[0]_INST_0_n_2\,
      CO(0) => \ap_return[0]_INST_0_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => b(3 downto 0),
      O(3 downto 0) => ap_return(3 downto 0),
      S(3) => \ap_return[0]_INST_0_i_1_n_0\,
      S(2) => \ap_return[0]_INST_0_i_2_n_0\,
      S(1) => \ap_return[0]_INST_0_i_3_n_0\,
      S(0) => \ap_return[0]_INST_0_i_4_n_0\
    );
\ap_return[0]_INST_0_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(3),
      I1 => a(3),
      O => \ap_return[0]_INST_0_i_1_n_0\
    );
\ap_return[0]_INST_0_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(2),
      I1 => a(2),
      O => \ap_return[0]_INST_0_i_2_n_0\
    );
\ap_return[0]_INST_0_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(1),
      I1 => a(1),
      O => \ap_return[0]_INST_0_i_3_n_0\
    );
\ap_return[0]_INST_0_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(0),
      I1 => a(0),
      O => \ap_return[0]_INST_0_i_4_n_0\
    );
\ap_return[12]_INST_0\: unisim.vcomponents.CARRY4
     port map (
      CI => \ap_return[8]_INST_0_n_0\,
      CO(3) => \ap_return[12]_INST_0_n_0\,
      CO(2) => \ap_return[12]_INST_0_n_1\,
      CO(1) => \ap_return[12]_INST_0_n_2\,
      CO(0) => \ap_return[12]_INST_0_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => b(15 downto 12),
      O(3 downto 0) => ap_return(15 downto 12),
      S(3) => \ap_return[12]_INST_0_i_1_n_0\,
      S(2) => \ap_return[12]_INST_0_i_2_n_0\,
      S(1) => \ap_return[12]_INST_0_i_3_n_0\,
      S(0) => \ap_return[12]_INST_0_i_4_n_0\
    );
\ap_return[12]_INST_0_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(15),
      I1 => a(15),
      O => \ap_return[12]_INST_0_i_1_n_0\
    );
\ap_return[12]_INST_0_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(14),
      I1 => a(14),
      O => \ap_return[12]_INST_0_i_2_n_0\
    );
\ap_return[12]_INST_0_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(13),
      I1 => a(13),
      O => \ap_return[12]_INST_0_i_3_n_0\
    );
\ap_return[12]_INST_0_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(12),
      I1 => a(12),
      O => \ap_return[12]_INST_0_i_4_n_0\
    );
\ap_return[16]_INST_0\: unisim.vcomponents.CARRY4
     port map (
      CI => \ap_return[12]_INST_0_n_0\,
      CO(3) => \ap_return[16]_INST_0_n_0\,
      CO(2) => \ap_return[16]_INST_0_n_1\,
      CO(1) => \ap_return[16]_INST_0_n_2\,
      CO(0) => \ap_return[16]_INST_0_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => b(19 downto 16),
      O(3 downto 0) => ap_return(19 downto 16),
      S(3) => \ap_return[16]_INST_0_i_1_n_0\,
      S(2) => \ap_return[16]_INST_0_i_2_n_0\,
      S(1) => \ap_return[16]_INST_0_i_3_n_0\,
      S(0) => \ap_return[16]_INST_0_i_4_n_0\
    );
\ap_return[16]_INST_0_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(19),
      I1 => a(19),
      O => \ap_return[16]_INST_0_i_1_n_0\
    );
\ap_return[16]_INST_0_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(18),
      I1 => a(18),
      O => \ap_return[16]_INST_0_i_2_n_0\
    );
\ap_return[16]_INST_0_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(17),
      I1 => a(17),
      O => \ap_return[16]_INST_0_i_3_n_0\
    );
\ap_return[16]_INST_0_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(16),
      I1 => a(16),
      O => \ap_return[16]_INST_0_i_4_n_0\
    );
\ap_return[20]_INST_0\: unisim.vcomponents.CARRY4
     port map (
      CI => \ap_return[16]_INST_0_n_0\,
      CO(3) => \ap_return[20]_INST_0_n_0\,
      CO(2) => \ap_return[20]_INST_0_n_1\,
      CO(1) => \ap_return[20]_INST_0_n_2\,
      CO(0) => \ap_return[20]_INST_0_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => b(23 downto 20),
      O(3 downto 0) => ap_return(23 downto 20),
      S(3) => \ap_return[20]_INST_0_i_1_n_0\,
      S(2) => \ap_return[20]_INST_0_i_2_n_0\,
      S(1) => \ap_return[20]_INST_0_i_3_n_0\,
      S(0) => \ap_return[20]_INST_0_i_4_n_0\
    );
\ap_return[20]_INST_0_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(23),
      I1 => a(23),
      O => \ap_return[20]_INST_0_i_1_n_0\
    );
\ap_return[20]_INST_0_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(22),
      I1 => a(22),
      O => \ap_return[20]_INST_0_i_2_n_0\
    );
\ap_return[20]_INST_0_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(21),
      I1 => a(21),
      O => \ap_return[20]_INST_0_i_3_n_0\
    );
\ap_return[20]_INST_0_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(20),
      I1 => a(20),
      O => \ap_return[20]_INST_0_i_4_n_0\
    );
\ap_return[24]_INST_0\: unisim.vcomponents.CARRY4
     port map (
      CI => \ap_return[20]_INST_0_n_0\,
      CO(3) => \ap_return[24]_INST_0_n_0\,
      CO(2) => \ap_return[24]_INST_0_n_1\,
      CO(1) => \ap_return[24]_INST_0_n_2\,
      CO(0) => \ap_return[24]_INST_0_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => b(27 downto 24),
      O(3 downto 0) => ap_return(27 downto 24),
      S(3) => \ap_return[24]_INST_0_i_1_n_0\,
      S(2) => \ap_return[24]_INST_0_i_2_n_0\,
      S(1) => \ap_return[24]_INST_0_i_3_n_0\,
      S(0) => \ap_return[24]_INST_0_i_4_n_0\
    );
\ap_return[24]_INST_0_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(27),
      I1 => a(27),
      O => \ap_return[24]_INST_0_i_1_n_0\
    );
\ap_return[24]_INST_0_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(26),
      I1 => a(26),
      O => \ap_return[24]_INST_0_i_2_n_0\
    );
\ap_return[24]_INST_0_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(25),
      I1 => a(25),
      O => \ap_return[24]_INST_0_i_3_n_0\
    );
\ap_return[24]_INST_0_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(24),
      I1 => a(24),
      O => \ap_return[24]_INST_0_i_4_n_0\
    );
\ap_return[28]_INST_0\: unisim.vcomponents.CARRY4
     port map (
      CI => \ap_return[24]_INST_0_n_0\,
      CO(3) => \NLW_ap_return[28]_INST_0_CO_UNCONNECTED\(3),
      CO(2) => \ap_return[28]_INST_0_n_1\,
      CO(1) => \ap_return[28]_INST_0_n_2\,
      CO(0) => \ap_return[28]_INST_0_n_3\,
      CYINIT => '0',
      DI(3) => '0',
      DI(2 downto 0) => b(30 downto 28),
      O(3 downto 0) => ap_return(31 downto 28),
      S(3) => \ap_return[28]_INST_0_i_1_n_0\,
      S(2) => \ap_return[28]_INST_0_i_2_n_0\,
      S(1) => \ap_return[28]_INST_0_i_3_n_0\,
      S(0) => \ap_return[28]_INST_0_i_4_n_0\
    );
\ap_return[28]_INST_0_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(31),
      I1 => a(31),
      O => \ap_return[28]_INST_0_i_1_n_0\
    );
\ap_return[28]_INST_0_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(30),
      I1 => a(30),
      O => \ap_return[28]_INST_0_i_2_n_0\
    );
\ap_return[28]_INST_0_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(29),
      I1 => a(29),
      O => \ap_return[28]_INST_0_i_3_n_0\
    );
\ap_return[28]_INST_0_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(28),
      I1 => a(28),
      O => \ap_return[28]_INST_0_i_4_n_0\
    );
\ap_return[4]_INST_0\: unisim.vcomponents.CARRY4
     port map (
      CI => \ap_return[0]_INST_0_n_0\,
      CO(3) => \ap_return[4]_INST_0_n_0\,
      CO(2) => \ap_return[4]_INST_0_n_1\,
      CO(1) => \ap_return[4]_INST_0_n_2\,
      CO(0) => \ap_return[4]_INST_0_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => b(7 downto 4),
      O(3 downto 0) => ap_return(7 downto 4),
      S(3) => \ap_return[4]_INST_0_i_1_n_0\,
      S(2) => \ap_return[4]_INST_0_i_2_n_0\,
      S(1) => \ap_return[4]_INST_0_i_3_n_0\,
      S(0) => \ap_return[4]_INST_0_i_4_n_0\
    );
\ap_return[4]_INST_0_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(7),
      I1 => a(7),
      O => \ap_return[4]_INST_0_i_1_n_0\
    );
\ap_return[4]_INST_0_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(6),
      I1 => a(6),
      O => \ap_return[4]_INST_0_i_2_n_0\
    );
\ap_return[4]_INST_0_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(5),
      I1 => a(5),
      O => \ap_return[4]_INST_0_i_3_n_0\
    );
\ap_return[4]_INST_0_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(4),
      I1 => a(4),
      O => \ap_return[4]_INST_0_i_4_n_0\
    );
\ap_return[8]_INST_0\: unisim.vcomponents.CARRY4
     port map (
      CI => \ap_return[4]_INST_0_n_0\,
      CO(3) => \ap_return[8]_INST_0_n_0\,
      CO(2) => \ap_return[8]_INST_0_n_1\,
      CO(1) => \ap_return[8]_INST_0_n_2\,
      CO(0) => \ap_return[8]_INST_0_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => b(11 downto 8),
      O(3 downto 0) => ap_return(11 downto 8),
      S(3) => \ap_return[8]_INST_0_i_1_n_0\,
      S(2) => \ap_return[8]_INST_0_i_2_n_0\,
      S(1) => \ap_return[8]_INST_0_i_3_n_0\,
      S(0) => \ap_return[8]_INST_0_i_4_n_0\
    );
\ap_return[8]_INST_0_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(11),
      I1 => a(11),
      O => \ap_return[8]_INST_0_i_1_n_0\
    );
\ap_return[8]_INST_0_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(10),
      I1 => a(10),
      O => \ap_return[8]_INST_0_i_2_n_0\
    );
\ap_return[8]_INST_0_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(9),
      I1 => a(9),
      O => \ap_return[8]_INST_0_i_3_n_0\
    );
\ap_return[8]_INST_0_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b(8),
      I1 => a(8),
      O => \ap_return[8]_INST_0_i_4_n_0\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  port (
    ap_start : in STD_LOGIC;
    ap_done : out STD_LOGIC;
    ap_idle : out STD_LOGIC;
    ap_ready : out STD_LOGIC;
    ap_return : out STD_LOGIC_VECTOR ( 31 downto 0 );
    a : in STD_LOGIC_VECTOR ( 31 downto 0 );
    b : in STD_LOGIC_VECTOR ( 31 downto 0 )
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "design_1_add_0_3,add,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "yes";
  attribute IP_DEFINITION_SOURCE : string;
  attribute IP_DEFINITION_SOURCE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "HLS";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "add,Vivado 2023.2";
  attribute hls_module : string;
  attribute hls_module of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "yes";
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  signal \<const1>\ : STD_LOGIC;
  signal NLW_inst_ap_idle_UNCONNECTED : STD_LOGIC;
  attribute SDX_KERNEL : string;
  attribute SDX_KERNEL of inst : label is "true";
  attribute SDX_KERNEL_SYNTH_INST : string;
  attribute SDX_KERNEL_SYNTH_INST of inst : label is "inst";
  attribute SDX_KERNEL_TYPE : string;
  attribute SDX_KERNEL_TYPE of inst : label is "hls";
  attribute X_INTERFACE_INFO : string;
  attribute X_INTERFACE_INFO of ap_done : signal is "xilinx.com:interface:acc_handshake:1.0 ap_ctrl done";
  attribute X_INTERFACE_INFO of ap_idle : signal is "xilinx.com:interface:acc_handshake:1.0 ap_ctrl idle";
  attribute X_INTERFACE_INFO of ap_ready : signal is "xilinx.com:interface:acc_handshake:1.0 ap_ctrl ready";
  attribute X_INTERFACE_INFO of ap_start : signal is "xilinx.com:interface:acc_handshake:1.0 ap_ctrl start";
  attribute X_INTERFACE_INFO of a : signal is "xilinx.com:signal:data:1.0 a DATA";
  attribute X_INTERFACE_PARAMETER : string;
  attribute X_INTERFACE_PARAMETER of a : signal is "XIL_INTERFACENAME a, LAYERED_METADATA undef";
  attribute X_INTERFACE_INFO of ap_return : signal is "xilinx.com:signal:data:1.0 ap_return DATA";
  attribute X_INTERFACE_PARAMETER of ap_return : signal is "XIL_INTERFACENAME ap_return, LAYERED_METADATA undef";
  attribute X_INTERFACE_INFO of b : signal is "xilinx.com:signal:data:1.0 b DATA";
  attribute X_INTERFACE_PARAMETER of b : signal is "XIL_INTERFACENAME b, LAYERED_METADATA undef";
begin
  ap_idle <= \<const1>\;
VCC: unisim.vcomponents.VCC
     port map (
      P => \<const1>\
    );
inst: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_add
     port map (
      a(31 downto 0) => a(31 downto 0),
      ap_done => ap_done,
      ap_idle => NLW_inst_ap_idle_UNCONNECTED,
      ap_ready => ap_ready,
      ap_return(31 downto 0) => ap_return(31 downto 0),
      ap_start => ap_start,
      b(31 downto 0) => b(31 downto 0)
    );
end STRUCTURE;
