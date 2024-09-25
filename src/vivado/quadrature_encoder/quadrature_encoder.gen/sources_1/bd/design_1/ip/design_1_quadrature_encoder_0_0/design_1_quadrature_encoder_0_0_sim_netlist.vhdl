-- Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2021.2 (win64) Build 3367213 Tue Oct 19 02:48:09 MDT 2021
-- Date        : Fri Jun 28 13:03:21 2024
-- Host        : Antonio running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim
--               c:/consegna/vivado/quadrature_encoder/quadrature_encoder.gen/sources_1/bd/design_1/ip/design_1_quadrature_encoder_0_0/design_1_quadrature_encoder_0_0_sim_netlist.vhdl
-- Design      : design_1_quadrature_encoder_0_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xc7z020clg400-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity design_1_quadrature_encoder_0_0_quadrature_encoder is
  port (
    direction : out STD_LOGIC;
    tick_count : out STD_LOGIC_VECTOR ( 31 downto 0 );
    clk : in STD_LOGIC;
    channelA : in STD_LOGIC;
    channelB : in STD_LOGIC;
    reset : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of design_1_quadrature_encoder_0_0_quadrature_encoder : entity is "quadrature_encoder";
end design_1_quadrature_encoder_0_0_quadrature_encoder;

architecture STRUCTURE of design_1_quadrature_encoder_0_0_quadrature_encoder is
  signal direction0 : STD_LOGIC;
  signal p_0_in : STD_LOGIC_VECTOR ( 1 to 1 );
  signal p_0_in0_in : STD_LOGIC;
  signal p_0_in_0 : STD_LOGIC;
  signal \p_0_in__0\ : STD_LOGIC_VECTOR ( 1 to 1 );
  signal p_1_in : STD_LOGIC;
  signal p_2_in : STD_LOGIC;
  signal \^tick_count\ : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \tick_count0__0\ : STD_LOGIC;
  signal \tick_count[31]_i_2_n_0\ : STD_LOGIC;
  signal \tick_count[3]_i_2_n_0\ : STD_LOGIC;
  signal \tick_count_reg[11]_i_1_n_0\ : STD_LOGIC;
  signal \tick_count_reg[11]_i_1_n_1\ : STD_LOGIC;
  signal \tick_count_reg[11]_i_1_n_2\ : STD_LOGIC;
  signal \tick_count_reg[11]_i_1_n_3\ : STD_LOGIC;
  signal \tick_count_reg[11]_i_1_n_4\ : STD_LOGIC;
  signal \tick_count_reg[11]_i_1_n_5\ : STD_LOGIC;
  signal \tick_count_reg[11]_i_1_n_6\ : STD_LOGIC;
  signal \tick_count_reg[11]_i_1_n_7\ : STD_LOGIC;
  signal \tick_count_reg[15]_i_1_n_0\ : STD_LOGIC;
  signal \tick_count_reg[15]_i_1_n_1\ : STD_LOGIC;
  signal \tick_count_reg[15]_i_1_n_2\ : STD_LOGIC;
  signal \tick_count_reg[15]_i_1_n_3\ : STD_LOGIC;
  signal \tick_count_reg[15]_i_1_n_4\ : STD_LOGIC;
  signal \tick_count_reg[15]_i_1_n_5\ : STD_LOGIC;
  signal \tick_count_reg[15]_i_1_n_6\ : STD_LOGIC;
  signal \tick_count_reg[15]_i_1_n_7\ : STD_LOGIC;
  signal \tick_count_reg[19]_i_1_n_0\ : STD_LOGIC;
  signal \tick_count_reg[19]_i_1_n_1\ : STD_LOGIC;
  signal \tick_count_reg[19]_i_1_n_2\ : STD_LOGIC;
  signal \tick_count_reg[19]_i_1_n_3\ : STD_LOGIC;
  signal \tick_count_reg[19]_i_1_n_4\ : STD_LOGIC;
  signal \tick_count_reg[19]_i_1_n_5\ : STD_LOGIC;
  signal \tick_count_reg[19]_i_1_n_6\ : STD_LOGIC;
  signal \tick_count_reg[19]_i_1_n_7\ : STD_LOGIC;
  signal \tick_count_reg[23]_i_1_n_0\ : STD_LOGIC;
  signal \tick_count_reg[23]_i_1_n_1\ : STD_LOGIC;
  signal \tick_count_reg[23]_i_1_n_2\ : STD_LOGIC;
  signal \tick_count_reg[23]_i_1_n_3\ : STD_LOGIC;
  signal \tick_count_reg[23]_i_1_n_4\ : STD_LOGIC;
  signal \tick_count_reg[23]_i_1_n_5\ : STD_LOGIC;
  signal \tick_count_reg[23]_i_1_n_6\ : STD_LOGIC;
  signal \tick_count_reg[23]_i_1_n_7\ : STD_LOGIC;
  signal \tick_count_reg[27]_i_1_n_0\ : STD_LOGIC;
  signal \tick_count_reg[27]_i_1_n_1\ : STD_LOGIC;
  signal \tick_count_reg[27]_i_1_n_2\ : STD_LOGIC;
  signal \tick_count_reg[27]_i_1_n_3\ : STD_LOGIC;
  signal \tick_count_reg[27]_i_1_n_4\ : STD_LOGIC;
  signal \tick_count_reg[27]_i_1_n_5\ : STD_LOGIC;
  signal \tick_count_reg[27]_i_1_n_6\ : STD_LOGIC;
  signal \tick_count_reg[27]_i_1_n_7\ : STD_LOGIC;
  signal \tick_count_reg[31]_i_1_n_1\ : STD_LOGIC;
  signal \tick_count_reg[31]_i_1_n_2\ : STD_LOGIC;
  signal \tick_count_reg[31]_i_1_n_3\ : STD_LOGIC;
  signal \tick_count_reg[31]_i_1_n_4\ : STD_LOGIC;
  signal \tick_count_reg[31]_i_1_n_5\ : STD_LOGIC;
  signal \tick_count_reg[31]_i_1_n_6\ : STD_LOGIC;
  signal \tick_count_reg[31]_i_1_n_7\ : STD_LOGIC;
  signal \tick_count_reg[3]_i_1_n_0\ : STD_LOGIC;
  signal \tick_count_reg[3]_i_1_n_1\ : STD_LOGIC;
  signal \tick_count_reg[3]_i_1_n_2\ : STD_LOGIC;
  signal \tick_count_reg[3]_i_1_n_3\ : STD_LOGIC;
  signal \tick_count_reg[3]_i_1_n_4\ : STD_LOGIC;
  signal \tick_count_reg[3]_i_1_n_5\ : STD_LOGIC;
  signal \tick_count_reg[3]_i_1_n_6\ : STD_LOGIC;
  signal \tick_count_reg[3]_i_1_n_7\ : STD_LOGIC;
  signal \tick_count_reg[7]_i_1_n_0\ : STD_LOGIC;
  signal \tick_count_reg[7]_i_1_n_1\ : STD_LOGIC;
  signal \tick_count_reg[7]_i_1_n_2\ : STD_LOGIC;
  signal \tick_count_reg[7]_i_1_n_3\ : STD_LOGIC;
  signal \tick_count_reg[7]_i_1_n_4\ : STD_LOGIC;
  signal \tick_count_reg[7]_i_1_n_5\ : STD_LOGIC;
  signal \tick_count_reg[7]_i_1_n_6\ : STD_LOGIC;
  signal \tick_count_reg[7]_i_1_n_7\ : STD_LOGIC;
  signal \NLW_tick_count_reg[31]_i_1_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 to 3 );
  attribute ADDER_THRESHOLD : integer;
  attribute ADDER_THRESHOLD of \tick_count_reg[11]_i_1\ : label is 11;
  attribute ADDER_THRESHOLD of \tick_count_reg[15]_i_1\ : label is 11;
  attribute ADDER_THRESHOLD of \tick_count_reg[19]_i_1\ : label is 11;
  attribute ADDER_THRESHOLD of \tick_count_reg[23]_i_1\ : label is 11;
  attribute ADDER_THRESHOLD of \tick_count_reg[27]_i_1\ : label is 11;
  attribute ADDER_THRESHOLD of \tick_count_reg[31]_i_1\ : label is 11;
  attribute ADDER_THRESHOLD of \tick_count_reg[3]_i_1\ : label is 11;
  attribute ADDER_THRESHOLD of \tick_count_reg[7]_i_1\ : label is 11;
begin
  tick_count(31 downto 0) <= \^tick_count\(31 downto 0);
\channelA_delayed_reg[0]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => '1',
      CLR => \tick_count[31]_i_2_n_0\,
      D => channelA,
      Q => p_0_in(1)
    );
\channelA_delayed_reg[1]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => '1',
      CLR => \tick_count[31]_i_2_n_0\,
      D => p_0_in(1),
      Q => p_1_in
    );
\channelA_delayed_reg[2]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => '1',
      CLR => \tick_count[31]_i_2_n_0\,
      D => p_1_in,
      Q => p_0_in0_in
    );
\channelB_delayed_reg[0]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => '1',
      CLR => \tick_count[31]_i_2_n_0\,
      D => channelB,
      Q => \p_0_in__0\(1)
    );
\channelB_delayed_reg[1]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => '1',
      CLR => \tick_count[31]_i_2_n_0\,
      D => \p_0_in__0\(1),
      Q => p_2_in
    );
\channelB_delayed_reg[2]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => '1',
      CLR => \tick_count[31]_i_2_n_0\,
      D => p_2_in,
      Q => p_0_in_0
    );
direction_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => p_0_in_0,
      I1 => p_1_in,
      O => direction0
    );
direction_reg: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => direction0,
      Q => direction
    );
tick_count0: unisim.vcomponents.LUT4
    generic map(
      INIT => X"6996"
    )
        port map (
      I0 => p_2_in,
      I1 => p_0_in0_in,
      I2 => p_1_in,
      I3 => p_0_in_0,
      O => \tick_count0__0\
    );
\tick_count[31]_i_2\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => reset,
      O => \tick_count[31]_i_2_n_0\
    );
\tick_count[3]_i_2\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^tick_count\(0),
      O => \tick_count[3]_i_2_n_0\
    );
\tick_count_reg[0]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[3]_i_1_n_7\,
      Q => \^tick_count\(0)
    );
\tick_count_reg[10]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[11]_i_1_n_5\,
      Q => \^tick_count\(10)
    );
\tick_count_reg[11]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[11]_i_1_n_4\,
      Q => \^tick_count\(11)
    );
\tick_count_reg[11]_i_1\: unisim.vcomponents.CARRY4
     port map (
      CI => \tick_count_reg[7]_i_1_n_0\,
      CO(3) => \tick_count_reg[11]_i_1_n_0\,
      CO(2) => \tick_count_reg[11]_i_1_n_1\,
      CO(1) => \tick_count_reg[11]_i_1_n_2\,
      CO(0) => \tick_count_reg[11]_i_1_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => B"0000",
      O(3) => \tick_count_reg[11]_i_1_n_4\,
      O(2) => \tick_count_reg[11]_i_1_n_5\,
      O(1) => \tick_count_reg[11]_i_1_n_6\,
      O(0) => \tick_count_reg[11]_i_1_n_7\,
      S(3 downto 0) => \^tick_count\(11 downto 8)
    );
\tick_count_reg[12]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[15]_i_1_n_7\,
      Q => \^tick_count\(12)
    );
\tick_count_reg[13]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[15]_i_1_n_6\,
      Q => \^tick_count\(13)
    );
\tick_count_reg[14]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[15]_i_1_n_5\,
      Q => \^tick_count\(14)
    );
\tick_count_reg[15]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[15]_i_1_n_4\,
      Q => \^tick_count\(15)
    );
\tick_count_reg[15]_i_1\: unisim.vcomponents.CARRY4
     port map (
      CI => \tick_count_reg[11]_i_1_n_0\,
      CO(3) => \tick_count_reg[15]_i_1_n_0\,
      CO(2) => \tick_count_reg[15]_i_1_n_1\,
      CO(1) => \tick_count_reg[15]_i_1_n_2\,
      CO(0) => \tick_count_reg[15]_i_1_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => B"0000",
      O(3) => \tick_count_reg[15]_i_1_n_4\,
      O(2) => \tick_count_reg[15]_i_1_n_5\,
      O(1) => \tick_count_reg[15]_i_1_n_6\,
      O(0) => \tick_count_reg[15]_i_1_n_7\,
      S(3 downto 0) => \^tick_count\(15 downto 12)
    );
\tick_count_reg[16]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[19]_i_1_n_7\,
      Q => \^tick_count\(16)
    );
\tick_count_reg[17]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[19]_i_1_n_6\,
      Q => \^tick_count\(17)
    );
\tick_count_reg[18]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[19]_i_1_n_5\,
      Q => \^tick_count\(18)
    );
\tick_count_reg[19]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[19]_i_1_n_4\,
      Q => \^tick_count\(19)
    );
\tick_count_reg[19]_i_1\: unisim.vcomponents.CARRY4
     port map (
      CI => \tick_count_reg[15]_i_1_n_0\,
      CO(3) => \tick_count_reg[19]_i_1_n_0\,
      CO(2) => \tick_count_reg[19]_i_1_n_1\,
      CO(1) => \tick_count_reg[19]_i_1_n_2\,
      CO(0) => \tick_count_reg[19]_i_1_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => B"0000",
      O(3) => \tick_count_reg[19]_i_1_n_4\,
      O(2) => \tick_count_reg[19]_i_1_n_5\,
      O(1) => \tick_count_reg[19]_i_1_n_6\,
      O(0) => \tick_count_reg[19]_i_1_n_7\,
      S(3 downto 0) => \^tick_count\(19 downto 16)
    );
\tick_count_reg[1]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[3]_i_1_n_6\,
      Q => \^tick_count\(1)
    );
\tick_count_reg[20]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[23]_i_1_n_7\,
      Q => \^tick_count\(20)
    );
\tick_count_reg[21]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[23]_i_1_n_6\,
      Q => \^tick_count\(21)
    );
\tick_count_reg[22]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[23]_i_1_n_5\,
      Q => \^tick_count\(22)
    );
\tick_count_reg[23]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[23]_i_1_n_4\,
      Q => \^tick_count\(23)
    );
\tick_count_reg[23]_i_1\: unisim.vcomponents.CARRY4
     port map (
      CI => \tick_count_reg[19]_i_1_n_0\,
      CO(3) => \tick_count_reg[23]_i_1_n_0\,
      CO(2) => \tick_count_reg[23]_i_1_n_1\,
      CO(1) => \tick_count_reg[23]_i_1_n_2\,
      CO(0) => \tick_count_reg[23]_i_1_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => B"0000",
      O(3) => \tick_count_reg[23]_i_1_n_4\,
      O(2) => \tick_count_reg[23]_i_1_n_5\,
      O(1) => \tick_count_reg[23]_i_1_n_6\,
      O(0) => \tick_count_reg[23]_i_1_n_7\,
      S(3 downto 0) => \^tick_count\(23 downto 20)
    );
\tick_count_reg[24]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[27]_i_1_n_7\,
      Q => \^tick_count\(24)
    );
\tick_count_reg[25]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[27]_i_1_n_6\,
      Q => \^tick_count\(25)
    );
\tick_count_reg[26]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[27]_i_1_n_5\,
      Q => \^tick_count\(26)
    );
\tick_count_reg[27]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[27]_i_1_n_4\,
      Q => \^tick_count\(27)
    );
\tick_count_reg[27]_i_1\: unisim.vcomponents.CARRY4
     port map (
      CI => \tick_count_reg[23]_i_1_n_0\,
      CO(3) => \tick_count_reg[27]_i_1_n_0\,
      CO(2) => \tick_count_reg[27]_i_1_n_1\,
      CO(1) => \tick_count_reg[27]_i_1_n_2\,
      CO(0) => \tick_count_reg[27]_i_1_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => B"0000",
      O(3) => \tick_count_reg[27]_i_1_n_4\,
      O(2) => \tick_count_reg[27]_i_1_n_5\,
      O(1) => \tick_count_reg[27]_i_1_n_6\,
      O(0) => \tick_count_reg[27]_i_1_n_7\,
      S(3 downto 0) => \^tick_count\(27 downto 24)
    );
\tick_count_reg[28]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[31]_i_1_n_7\,
      Q => \^tick_count\(28)
    );
\tick_count_reg[29]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[31]_i_1_n_6\,
      Q => \^tick_count\(29)
    );
\tick_count_reg[2]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[3]_i_1_n_5\,
      Q => \^tick_count\(2)
    );
\tick_count_reg[30]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[31]_i_1_n_5\,
      Q => \^tick_count\(30)
    );
\tick_count_reg[31]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[31]_i_1_n_4\,
      Q => \^tick_count\(31)
    );
\tick_count_reg[31]_i_1\: unisim.vcomponents.CARRY4
     port map (
      CI => \tick_count_reg[27]_i_1_n_0\,
      CO(3) => \NLW_tick_count_reg[31]_i_1_CO_UNCONNECTED\(3),
      CO(2) => \tick_count_reg[31]_i_1_n_1\,
      CO(1) => \tick_count_reg[31]_i_1_n_2\,
      CO(0) => \tick_count_reg[31]_i_1_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => B"0000",
      O(3) => \tick_count_reg[31]_i_1_n_4\,
      O(2) => \tick_count_reg[31]_i_1_n_5\,
      O(1) => \tick_count_reg[31]_i_1_n_6\,
      O(0) => \tick_count_reg[31]_i_1_n_7\,
      S(3 downto 0) => \^tick_count\(31 downto 28)
    );
\tick_count_reg[3]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[3]_i_1_n_4\,
      Q => \^tick_count\(3)
    );
\tick_count_reg[3]_i_1\: unisim.vcomponents.CARRY4
     port map (
      CI => '0',
      CO(3) => \tick_count_reg[3]_i_1_n_0\,
      CO(2) => \tick_count_reg[3]_i_1_n_1\,
      CO(1) => \tick_count_reg[3]_i_1_n_2\,
      CO(0) => \tick_count_reg[3]_i_1_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => B"0001",
      O(3) => \tick_count_reg[3]_i_1_n_4\,
      O(2) => \tick_count_reg[3]_i_1_n_5\,
      O(1) => \tick_count_reg[3]_i_1_n_6\,
      O(0) => \tick_count_reg[3]_i_1_n_7\,
      S(3 downto 1) => \^tick_count\(3 downto 1),
      S(0) => \tick_count[3]_i_2_n_0\
    );
\tick_count_reg[4]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[7]_i_1_n_7\,
      Q => \^tick_count\(4)
    );
\tick_count_reg[5]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[7]_i_1_n_6\,
      Q => \^tick_count\(5)
    );
\tick_count_reg[6]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[7]_i_1_n_5\,
      Q => \^tick_count\(6)
    );
\tick_count_reg[7]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[7]_i_1_n_4\,
      Q => \^tick_count\(7)
    );
\tick_count_reg[7]_i_1\: unisim.vcomponents.CARRY4
     port map (
      CI => \tick_count_reg[3]_i_1_n_0\,
      CO(3) => \tick_count_reg[7]_i_1_n_0\,
      CO(2) => \tick_count_reg[7]_i_1_n_1\,
      CO(1) => \tick_count_reg[7]_i_1_n_2\,
      CO(0) => \tick_count_reg[7]_i_1_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => B"0000",
      O(3) => \tick_count_reg[7]_i_1_n_4\,
      O(2) => \tick_count_reg[7]_i_1_n_5\,
      O(1) => \tick_count_reg[7]_i_1_n_6\,
      O(0) => \tick_count_reg[7]_i_1_n_7\,
      S(3 downto 0) => \^tick_count\(7 downto 4)
    );
\tick_count_reg[8]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[11]_i_1_n_7\,
      Q => \^tick_count\(8)
    );
\tick_count_reg[9]\: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => \tick_count0__0\,
      CLR => \tick_count[31]_i_2_n_0\,
      D => \tick_count_reg[11]_i_1_n_6\,
      Q => \^tick_count\(9)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity design_1_quadrature_encoder_0_0 is
  port (
    clk : in STD_LOGIC;
    reset : in STD_LOGIC;
    channelA : in STD_LOGIC;
    channelB : in STD_LOGIC;
    tick_count : out STD_LOGIC_VECTOR ( 31 downto 0 );
    direction : out STD_LOGIC
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of design_1_quadrature_encoder_0_0 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of design_1_quadrature_encoder_0_0 : entity is "design_1_quadrature_encoder_0_0,quadrature_encoder,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of design_1_quadrature_encoder_0_0 : entity is "yes";
  attribute IP_DEFINITION_SOURCE : string;
  attribute IP_DEFINITION_SOURCE of design_1_quadrature_encoder_0_0 : entity is "module_ref";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of design_1_quadrature_encoder_0_0 : entity is "quadrature_encoder,Vivado 2021.2";
end design_1_quadrature_encoder_0_0;

architecture STRUCTURE of design_1_quadrature_encoder_0_0 is
  attribute X_INTERFACE_INFO : string;
  attribute X_INTERFACE_INFO of clk : signal is "xilinx.com:signal:clock:1.0 clk CLK";
  attribute X_INTERFACE_PARAMETER : string;
  attribute X_INTERFACE_PARAMETER of clk : signal is "XIL_INTERFACENAME clk, ASSOCIATED_RESET reset, FREQ_HZ 5e+07, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN design_1_processing_system7_0_0_FCLK_CLK0, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of reset : signal is "xilinx.com:signal:reset:1.0 reset RST";
  attribute X_INTERFACE_PARAMETER of reset : signal is "XIL_INTERFACENAME reset, POLARITY ACTIVE_LOW, INSERT_VIP 0";
begin
inst: entity work.design_1_quadrature_encoder_0_0_quadrature_encoder
     port map (
      channelA => channelA,
      channelB => channelB,
      clk => clk,
      direction => direction,
      reset => reset,
      tick_count(31 downto 0) => tick_count(31 downto 0)
    );
end STRUCTURE;
