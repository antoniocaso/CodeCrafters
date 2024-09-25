// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2021.2 (win64) Build 3367213 Tue Oct 19 02:48:09 MDT 2021
// Date        : Thu Jun 27 16:22:53 2024
// Host        : Antonio running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ design_1_PmodOLEDrgb_0_1_stub.v
// Design      : design_1_PmodOLEDrgb_0_1
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z020clg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "PmodOLEDrgb_v1_0,Vivado 2021.2" *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix(ext_spi_clk, pmod_out_pin10_i, 
  pmod_out_pin10_o, pmod_out_pin10_t, pmod_out_pin1_i, pmod_out_pin1_o, pmod_out_pin1_t, 
  pmod_out_pin2_i, pmod_out_pin2_o, pmod_out_pin2_t, pmod_out_pin3_i, pmod_out_pin3_o, 
  pmod_out_pin3_t, pmod_out_pin4_i, pmod_out_pin4_o, pmod_out_pin4_t, pmod_out_pin7_i, 
  pmod_out_pin7_o, pmod_out_pin7_t, pmod_out_pin8_i, pmod_out_pin8_o, pmod_out_pin8_t, 
  pmod_out_pin9_i, pmod_out_pin9_o, pmod_out_pin9_t, s_axi_aclk, s_axi_aclk2, s_axi_aresetn, 
  axi_lite_gpio_awaddr, axi_lite_gpio_awprot, axi_lite_gpio_awvalid, 
  axi_lite_gpio_awready, axi_lite_gpio_wdata, axi_lite_gpio_wstrb, axi_lite_gpio_wvalid, 
  axi_lite_gpio_wready, axi_lite_gpio_bresp, axi_lite_gpio_bvalid, axi_lite_gpio_bready, 
  axi_lite_gpio_araddr, axi_lite_gpio_arprot, axi_lite_gpio_arvalid, 
  axi_lite_gpio_arready, axi_lite_gpio_rdata, axi_lite_gpio_rresp, axi_lite_gpio_rvalid, 
  axi_lite_gpio_rready, axi_lite_spi_awaddr, axi_lite_spi_awprot, axi_lite_spi_awvalid, 
  axi_lite_spi_awready, axi_lite_spi_wdata, axi_lite_spi_wstrb, axi_lite_spi_wvalid, 
  axi_lite_spi_wready, axi_lite_spi_bresp, axi_lite_spi_bvalid, axi_lite_spi_bready, 
  axi_lite_spi_araddr, axi_lite_spi_arprot, axi_lite_spi_arvalid, axi_lite_spi_arready, 
  axi_lite_spi_rdata, axi_lite_spi_rresp, axi_lite_spi_rvalid, axi_lite_spi_rready)
/* synthesis syn_black_box black_box_pad_pin="ext_spi_clk,pmod_out_pin10_i,pmod_out_pin10_o,pmod_out_pin10_t,pmod_out_pin1_i,pmod_out_pin1_o,pmod_out_pin1_t,pmod_out_pin2_i,pmod_out_pin2_o,pmod_out_pin2_t,pmod_out_pin3_i,pmod_out_pin3_o,pmod_out_pin3_t,pmod_out_pin4_i,pmod_out_pin4_o,pmod_out_pin4_t,pmod_out_pin7_i,pmod_out_pin7_o,pmod_out_pin7_t,pmod_out_pin8_i,pmod_out_pin8_o,pmod_out_pin8_t,pmod_out_pin9_i,pmod_out_pin9_o,pmod_out_pin9_t,s_axi_aclk,s_axi_aclk2,s_axi_aresetn,axi_lite_gpio_awaddr[8:0],axi_lite_gpio_awprot[2:0],axi_lite_gpio_awvalid,axi_lite_gpio_awready,axi_lite_gpio_wdata[31:0],axi_lite_gpio_wstrb[3:0],axi_lite_gpio_wvalid,axi_lite_gpio_wready,axi_lite_gpio_bresp[1:0],axi_lite_gpio_bvalid,axi_lite_gpio_bready,axi_lite_gpio_araddr[8:0],axi_lite_gpio_arprot[2:0],axi_lite_gpio_arvalid,axi_lite_gpio_arready,axi_lite_gpio_rdata[31:0],axi_lite_gpio_rresp[1:0],axi_lite_gpio_rvalid,axi_lite_gpio_rready,axi_lite_spi_awaddr[6:0],axi_lite_spi_awprot[2:0],axi_lite_spi_awvalid,axi_lite_spi_awready,axi_lite_spi_wdata[31:0],axi_lite_spi_wstrb[3:0],axi_lite_spi_wvalid,axi_lite_spi_wready,axi_lite_spi_bresp[1:0],axi_lite_spi_bvalid,axi_lite_spi_bready,axi_lite_spi_araddr[6:0],axi_lite_spi_arprot[2:0],axi_lite_spi_arvalid,axi_lite_spi_arready,axi_lite_spi_rdata[31:0],axi_lite_spi_rresp[1:0],axi_lite_spi_rvalid,axi_lite_spi_rready" */;
  input ext_spi_clk;
  input pmod_out_pin10_i;
  output pmod_out_pin10_o;
  output pmod_out_pin10_t;
  input pmod_out_pin1_i;
  output pmod_out_pin1_o;
  output pmod_out_pin1_t;
  input pmod_out_pin2_i;
  output pmod_out_pin2_o;
  output pmod_out_pin2_t;
  input pmod_out_pin3_i;
  output pmod_out_pin3_o;
  output pmod_out_pin3_t;
  input pmod_out_pin4_i;
  output pmod_out_pin4_o;
  output pmod_out_pin4_t;
  input pmod_out_pin7_i;
  output pmod_out_pin7_o;
  output pmod_out_pin7_t;
  input pmod_out_pin8_i;
  output pmod_out_pin8_o;
  output pmod_out_pin8_t;
  input pmod_out_pin9_i;
  output pmod_out_pin9_o;
  output pmod_out_pin9_t;
  input s_axi_aclk;
  input s_axi_aclk2;
  input s_axi_aresetn;
  input [8:0]axi_lite_gpio_awaddr;
  input [2:0]axi_lite_gpio_awprot;
  input axi_lite_gpio_awvalid;
  output axi_lite_gpio_awready;
  input [31:0]axi_lite_gpio_wdata;
  input [3:0]axi_lite_gpio_wstrb;
  input axi_lite_gpio_wvalid;
  output axi_lite_gpio_wready;
  output [1:0]axi_lite_gpio_bresp;
  output axi_lite_gpio_bvalid;
  input axi_lite_gpio_bready;
  input [8:0]axi_lite_gpio_araddr;
  input [2:0]axi_lite_gpio_arprot;
  input axi_lite_gpio_arvalid;
  output axi_lite_gpio_arready;
  output [31:0]axi_lite_gpio_rdata;
  output [1:0]axi_lite_gpio_rresp;
  output axi_lite_gpio_rvalid;
  input axi_lite_gpio_rready;
  input [6:0]axi_lite_spi_awaddr;
  input [2:0]axi_lite_spi_awprot;
  input axi_lite_spi_awvalid;
  output axi_lite_spi_awready;
  input [31:0]axi_lite_spi_wdata;
  input [3:0]axi_lite_spi_wstrb;
  input axi_lite_spi_wvalid;
  output axi_lite_spi_wready;
  output [1:0]axi_lite_spi_bresp;
  output axi_lite_spi_bvalid;
  input axi_lite_spi_bready;
  input [6:0]axi_lite_spi_araddr;
  input [2:0]axi_lite_spi_arprot;
  input axi_lite_spi_arvalid;
  output axi_lite_spi_arready;
  output [31:0]axi_lite_spi_rdata;
  output [1:0]axi_lite_spi_rresp;
  output axi_lite_spi_rvalid;
  input axi_lite_spi_rready;
endmodule
