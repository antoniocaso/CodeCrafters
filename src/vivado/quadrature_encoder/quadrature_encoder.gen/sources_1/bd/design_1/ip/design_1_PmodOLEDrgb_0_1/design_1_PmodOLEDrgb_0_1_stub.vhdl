-- Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2021.2 (win64) Build 3367213 Tue Oct 19 02:48:09 MDT 2021
-- Date        : Thu Jun 27 16:22:54 2024
-- Host        : Antonio running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/consegna/quadrature_encoder/quadrature_encoder.gen/sources_1/bd/design_1/ip/design_1_PmodOLEDrgb_0_1/design_1_PmodOLEDrgb_0_1_stub.vhdl
-- Design      : design_1_PmodOLEDrgb_0_1
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7z020clg400-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity design_1_PmodOLEDrgb_0_1 is
  Port ( 
    ext_spi_clk : in STD_LOGIC;
    pmod_out_pin10_i : in STD_LOGIC;
    pmod_out_pin10_o : out STD_LOGIC;
    pmod_out_pin10_t : out STD_LOGIC;
    pmod_out_pin1_i : in STD_LOGIC;
    pmod_out_pin1_o : out STD_LOGIC;
    pmod_out_pin1_t : out STD_LOGIC;
    pmod_out_pin2_i : in STD_LOGIC;
    pmod_out_pin2_o : out STD_LOGIC;
    pmod_out_pin2_t : out STD_LOGIC;
    pmod_out_pin3_i : in STD_LOGIC;
    pmod_out_pin3_o : out STD_LOGIC;
    pmod_out_pin3_t : out STD_LOGIC;
    pmod_out_pin4_i : in STD_LOGIC;
    pmod_out_pin4_o : out STD_LOGIC;
    pmod_out_pin4_t : out STD_LOGIC;
    pmod_out_pin7_i : in STD_LOGIC;
    pmod_out_pin7_o : out STD_LOGIC;
    pmod_out_pin7_t : out STD_LOGIC;
    pmod_out_pin8_i : in STD_LOGIC;
    pmod_out_pin8_o : out STD_LOGIC;
    pmod_out_pin8_t : out STD_LOGIC;
    pmod_out_pin9_i : in STD_LOGIC;
    pmod_out_pin9_o : out STD_LOGIC;
    pmod_out_pin9_t : out STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    s_axi_aclk2 : in STD_LOGIC;
    s_axi_aresetn : in STD_LOGIC;
    axi_lite_gpio_awaddr : in STD_LOGIC_VECTOR ( 8 downto 0 );
    axi_lite_gpio_awprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    axi_lite_gpio_awvalid : in STD_LOGIC;
    axi_lite_gpio_awready : out STD_LOGIC;
    axi_lite_gpio_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    axi_lite_gpio_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    axi_lite_gpio_wvalid : in STD_LOGIC;
    axi_lite_gpio_wready : out STD_LOGIC;
    axi_lite_gpio_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    axi_lite_gpio_bvalid : out STD_LOGIC;
    axi_lite_gpio_bready : in STD_LOGIC;
    axi_lite_gpio_araddr : in STD_LOGIC_VECTOR ( 8 downto 0 );
    axi_lite_gpio_arprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    axi_lite_gpio_arvalid : in STD_LOGIC;
    axi_lite_gpio_arready : out STD_LOGIC;
    axi_lite_gpio_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    axi_lite_gpio_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    axi_lite_gpio_rvalid : out STD_LOGIC;
    axi_lite_gpio_rready : in STD_LOGIC;
    axi_lite_spi_awaddr : in STD_LOGIC_VECTOR ( 6 downto 0 );
    axi_lite_spi_awprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    axi_lite_spi_awvalid : in STD_LOGIC;
    axi_lite_spi_awready : out STD_LOGIC;
    axi_lite_spi_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    axi_lite_spi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    axi_lite_spi_wvalid : in STD_LOGIC;
    axi_lite_spi_wready : out STD_LOGIC;
    axi_lite_spi_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    axi_lite_spi_bvalid : out STD_LOGIC;
    axi_lite_spi_bready : in STD_LOGIC;
    axi_lite_spi_araddr : in STD_LOGIC_VECTOR ( 6 downto 0 );
    axi_lite_spi_arprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    axi_lite_spi_arvalid : in STD_LOGIC;
    axi_lite_spi_arready : out STD_LOGIC;
    axi_lite_spi_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    axi_lite_spi_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    axi_lite_spi_rvalid : out STD_LOGIC;
    axi_lite_spi_rready : in STD_LOGIC
  );

end design_1_PmodOLEDrgb_0_1;

architecture stub of design_1_PmodOLEDrgb_0_1 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "ext_spi_clk,pmod_out_pin10_i,pmod_out_pin10_o,pmod_out_pin10_t,pmod_out_pin1_i,pmod_out_pin1_o,pmod_out_pin1_t,pmod_out_pin2_i,pmod_out_pin2_o,pmod_out_pin2_t,pmod_out_pin3_i,pmod_out_pin3_o,pmod_out_pin3_t,pmod_out_pin4_i,pmod_out_pin4_o,pmod_out_pin4_t,pmod_out_pin7_i,pmod_out_pin7_o,pmod_out_pin7_t,pmod_out_pin8_i,pmod_out_pin8_o,pmod_out_pin8_t,pmod_out_pin9_i,pmod_out_pin9_o,pmod_out_pin9_t,s_axi_aclk,s_axi_aclk2,s_axi_aresetn,axi_lite_gpio_awaddr[8:0],axi_lite_gpio_awprot[2:0],axi_lite_gpio_awvalid,axi_lite_gpio_awready,axi_lite_gpio_wdata[31:0],axi_lite_gpio_wstrb[3:0],axi_lite_gpio_wvalid,axi_lite_gpio_wready,axi_lite_gpio_bresp[1:0],axi_lite_gpio_bvalid,axi_lite_gpio_bready,axi_lite_gpio_araddr[8:0],axi_lite_gpio_arprot[2:0],axi_lite_gpio_arvalid,axi_lite_gpio_arready,axi_lite_gpio_rdata[31:0],axi_lite_gpio_rresp[1:0],axi_lite_gpio_rvalid,axi_lite_gpio_rready,axi_lite_spi_awaddr[6:0],axi_lite_spi_awprot[2:0],axi_lite_spi_awvalid,axi_lite_spi_awready,axi_lite_spi_wdata[31:0],axi_lite_spi_wstrb[3:0],axi_lite_spi_wvalid,axi_lite_spi_wready,axi_lite_spi_bresp[1:0],axi_lite_spi_bvalid,axi_lite_spi_bready,axi_lite_spi_araddr[6:0],axi_lite_spi_arprot[2:0],axi_lite_spi_arvalid,axi_lite_spi_arready,axi_lite_spi_rdata[31:0],axi_lite_spi_rresp[1:0],axi_lite_spi_rvalid,axi_lite_spi_rready";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "PmodOLEDrgb_v1_0,Vivado 2021.2";
begin
end;
