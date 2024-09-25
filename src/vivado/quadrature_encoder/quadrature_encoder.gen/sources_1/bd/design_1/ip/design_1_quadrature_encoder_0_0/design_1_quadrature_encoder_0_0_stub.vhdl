-- Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2021.2 (win64) Build 3367213 Tue Oct 19 02:48:09 MDT 2021
-- Date        : Fri Jun 28 13:03:21 2024
-- Host        : Antonio running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/consegna/vivado/quadrature_encoder/quadrature_encoder.gen/sources_1/bd/design_1/ip/design_1_quadrature_encoder_0_0/design_1_quadrature_encoder_0_0_stub.vhdl
-- Design      : design_1_quadrature_encoder_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7z020clg400-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity design_1_quadrature_encoder_0_0 is
  Port ( 
    clk : in STD_LOGIC;
    reset : in STD_LOGIC;
    channelA : in STD_LOGIC;
    channelB : in STD_LOGIC;
    tick_count : out STD_LOGIC_VECTOR ( 31 downto 0 );
    direction : out STD_LOGIC
  );

end design_1_quadrature_encoder_0_0;

architecture stub of design_1_quadrature_encoder_0_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "clk,reset,channelA,channelB,tick_count[31:0],direction";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "quadrature_encoder,Vivado 2021.2";
begin
end;
