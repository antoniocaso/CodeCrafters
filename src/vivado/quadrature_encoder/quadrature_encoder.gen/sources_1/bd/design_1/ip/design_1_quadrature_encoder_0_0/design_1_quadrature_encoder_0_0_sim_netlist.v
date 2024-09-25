// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2021.2 (win64) Build 3367213 Tue Oct 19 02:48:09 MDT 2021
// Date        : Fri Jun 28 13:03:21 2024
// Host        : Antonio running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               c:/consegna/vivado/quadrature_encoder/quadrature_encoder.gen/sources_1/bd/design_1/ip/design_1_quadrature_encoder_0_0/design_1_quadrature_encoder_0_0_sim_netlist.v
// Design      : design_1_quadrature_encoder_0_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7z020clg400-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "design_1_quadrature_encoder_0_0,quadrature_encoder,{}" *) (* DowngradeIPIdentifiedWarnings = "yes" *) (* IP_DEFINITION_SOURCE = "module_ref" *) 
(* X_CORE_INFO = "quadrature_encoder,Vivado 2021.2" *) 
(* NotValidForBitStream *)
module design_1_quadrature_encoder_0_0
   (clk,
    reset,
    channelA,
    channelB,
    tick_count,
    direction);
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 clk CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME clk, ASSOCIATED_RESET reset, FREQ_HZ 5e+07, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN design_1_processing_system7_0_0_FCLK_CLK0, INSERT_VIP 0" *) input clk;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 reset RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME reset, POLARITY ACTIVE_LOW, INSERT_VIP 0" *) input reset;
  input channelA;
  input channelB;
  output [31:0]tick_count;
  output direction;

  wire channelA;
  wire channelB;
  wire clk;
  wire direction;
  wire reset;
  wire [31:0]tick_count;

  design_1_quadrature_encoder_0_0_quadrature_encoder inst
       (.channelA(channelA),
        .channelB(channelB),
        .clk(clk),
        .direction(direction),
        .reset(reset),
        .tick_count(tick_count));
endmodule

(* ORIG_REF_NAME = "quadrature_encoder" *) 
module design_1_quadrature_encoder_0_0_quadrature_encoder
   (direction,
    tick_count,
    clk,
    channelA,
    channelB,
    reset);
  output direction;
  output [31:0]tick_count;
  input clk;
  input channelA;
  input channelB;
  input reset;

  wire channelA;
  wire channelB;
  wire clk;
  wire direction;
  wire direction0;
  wire [1:1]p_0_in;
  wire p_0_in0_in;
  wire p_0_in_0;
  wire [1:1]p_0_in__0;
  wire p_1_in;
  wire p_2_in;
  wire reset;
  wire [31:0]tick_count;
  wire tick_count0__0;
  wire \tick_count[31]_i_2_n_0 ;
  wire \tick_count[3]_i_2_n_0 ;
  wire \tick_count_reg[11]_i_1_n_0 ;
  wire \tick_count_reg[11]_i_1_n_1 ;
  wire \tick_count_reg[11]_i_1_n_2 ;
  wire \tick_count_reg[11]_i_1_n_3 ;
  wire \tick_count_reg[11]_i_1_n_4 ;
  wire \tick_count_reg[11]_i_1_n_5 ;
  wire \tick_count_reg[11]_i_1_n_6 ;
  wire \tick_count_reg[11]_i_1_n_7 ;
  wire \tick_count_reg[15]_i_1_n_0 ;
  wire \tick_count_reg[15]_i_1_n_1 ;
  wire \tick_count_reg[15]_i_1_n_2 ;
  wire \tick_count_reg[15]_i_1_n_3 ;
  wire \tick_count_reg[15]_i_1_n_4 ;
  wire \tick_count_reg[15]_i_1_n_5 ;
  wire \tick_count_reg[15]_i_1_n_6 ;
  wire \tick_count_reg[15]_i_1_n_7 ;
  wire \tick_count_reg[19]_i_1_n_0 ;
  wire \tick_count_reg[19]_i_1_n_1 ;
  wire \tick_count_reg[19]_i_1_n_2 ;
  wire \tick_count_reg[19]_i_1_n_3 ;
  wire \tick_count_reg[19]_i_1_n_4 ;
  wire \tick_count_reg[19]_i_1_n_5 ;
  wire \tick_count_reg[19]_i_1_n_6 ;
  wire \tick_count_reg[19]_i_1_n_7 ;
  wire \tick_count_reg[23]_i_1_n_0 ;
  wire \tick_count_reg[23]_i_1_n_1 ;
  wire \tick_count_reg[23]_i_1_n_2 ;
  wire \tick_count_reg[23]_i_1_n_3 ;
  wire \tick_count_reg[23]_i_1_n_4 ;
  wire \tick_count_reg[23]_i_1_n_5 ;
  wire \tick_count_reg[23]_i_1_n_6 ;
  wire \tick_count_reg[23]_i_1_n_7 ;
  wire \tick_count_reg[27]_i_1_n_0 ;
  wire \tick_count_reg[27]_i_1_n_1 ;
  wire \tick_count_reg[27]_i_1_n_2 ;
  wire \tick_count_reg[27]_i_1_n_3 ;
  wire \tick_count_reg[27]_i_1_n_4 ;
  wire \tick_count_reg[27]_i_1_n_5 ;
  wire \tick_count_reg[27]_i_1_n_6 ;
  wire \tick_count_reg[27]_i_1_n_7 ;
  wire \tick_count_reg[31]_i_1_n_1 ;
  wire \tick_count_reg[31]_i_1_n_2 ;
  wire \tick_count_reg[31]_i_1_n_3 ;
  wire \tick_count_reg[31]_i_1_n_4 ;
  wire \tick_count_reg[31]_i_1_n_5 ;
  wire \tick_count_reg[31]_i_1_n_6 ;
  wire \tick_count_reg[31]_i_1_n_7 ;
  wire \tick_count_reg[3]_i_1_n_0 ;
  wire \tick_count_reg[3]_i_1_n_1 ;
  wire \tick_count_reg[3]_i_1_n_2 ;
  wire \tick_count_reg[3]_i_1_n_3 ;
  wire \tick_count_reg[3]_i_1_n_4 ;
  wire \tick_count_reg[3]_i_1_n_5 ;
  wire \tick_count_reg[3]_i_1_n_6 ;
  wire \tick_count_reg[3]_i_1_n_7 ;
  wire \tick_count_reg[7]_i_1_n_0 ;
  wire \tick_count_reg[7]_i_1_n_1 ;
  wire \tick_count_reg[7]_i_1_n_2 ;
  wire \tick_count_reg[7]_i_1_n_3 ;
  wire \tick_count_reg[7]_i_1_n_4 ;
  wire \tick_count_reg[7]_i_1_n_5 ;
  wire \tick_count_reg[7]_i_1_n_6 ;
  wire \tick_count_reg[7]_i_1_n_7 ;
  wire [3:3]\NLW_tick_count_reg[31]_i_1_CO_UNCONNECTED ;

  FDCE \channelA_delayed_reg[0] 
       (.C(clk),
        .CE(1'b1),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(channelA),
        .Q(p_0_in));
  FDCE \channelA_delayed_reg[1] 
       (.C(clk),
        .CE(1'b1),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(p_0_in),
        .Q(p_1_in));
  FDCE \channelA_delayed_reg[2] 
       (.C(clk),
        .CE(1'b1),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(p_1_in),
        .Q(p_0_in0_in));
  FDCE \channelB_delayed_reg[0] 
       (.C(clk),
        .CE(1'b1),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(channelB),
        .Q(p_0_in__0));
  FDCE \channelB_delayed_reg[1] 
       (.C(clk),
        .CE(1'b1),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(p_0_in__0),
        .Q(p_2_in));
  FDCE \channelB_delayed_reg[2] 
       (.C(clk),
        .CE(1'b1),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(p_2_in),
        .Q(p_0_in_0));
  LUT2 #(
    .INIT(4'h6)) 
    direction_i_1
       (.I0(p_0_in_0),
        .I1(p_1_in),
        .O(direction0));
  FDCE direction_reg
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(direction0),
        .Q(direction));
  LUT4 #(
    .INIT(16'h6996)) 
    tick_count0
       (.I0(p_2_in),
        .I1(p_0_in0_in),
        .I2(p_1_in),
        .I3(p_0_in_0),
        .O(tick_count0__0));
  LUT1 #(
    .INIT(2'h1)) 
    \tick_count[31]_i_2 
       (.I0(reset),
        .O(\tick_count[31]_i_2_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \tick_count[3]_i_2 
       (.I0(tick_count[0]),
        .O(\tick_count[3]_i_2_n_0 ));
  FDCE \tick_count_reg[0] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[3]_i_1_n_7 ),
        .Q(tick_count[0]));
  FDCE \tick_count_reg[10] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[11]_i_1_n_5 ),
        .Q(tick_count[10]));
  FDCE \tick_count_reg[11] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[11]_i_1_n_4 ),
        .Q(tick_count[11]));
  (* ADDER_THRESHOLD = "11" *) 
  CARRY4 \tick_count_reg[11]_i_1 
       (.CI(\tick_count_reg[7]_i_1_n_0 ),
        .CO({\tick_count_reg[11]_i_1_n_0 ,\tick_count_reg[11]_i_1_n_1 ,\tick_count_reg[11]_i_1_n_2 ,\tick_count_reg[11]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\tick_count_reg[11]_i_1_n_4 ,\tick_count_reg[11]_i_1_n_5 ,\tick_count_reg[11]_i_1_n_6 ,\tick_count_reg[11]_i_1_n_7 }),
        .S(tick_count[11:8]));
  FDCE \tick_count_reg[12] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[15]_i_1_n_7 ),
        .Q(tick_count[12]));
  FDCE \tick_count_reg[13] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[15]_i_1_n_6 ),
        .Q(tick_count[13]));
  FDCE \tick_count_reg[14] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[15]_i_1_n_5 ),
        .Q(tick_count[14]));
  FDCE \tick_count_reg[15] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[15]_i_1_n_4 ),
        .Q(tick_count[15]));
  (* ADDER_THRESHOLD = "11" *) 
  CARRY4 \tick_count_reg[15]_i_1 
       (.CI(\tick_count_reg[11]_i_1_n_0 ),
        .CO({\tick_count_reg[15]_i_1_n_0 ,\tick_count_reg[15]_i_1_n_1 ,\tick_count_reg[15]_i_1_n_2 ,\tick_count_reg[15]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\tick_count_reg[15]_i_1_n_4 ,\tick_count_reg[15]_i_1_n_5 ,\tick_count_reg[15]_i_1_n_6 ,\tick_count_reg[15]_i_1_n_7 }),
        .S(tick_count[15:12]));
  FDCE \tick_count_reg[16] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[19]_i_1_n_7 ),
        .Q(tick_count[16]));
  FDCE \tick_count_reg[17] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[19]_i_1_n_6 ),
        .Q(tick_count[17]));
  FDCE \tick_count_reg[18] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[19]_i_1_n_5 ),
        .Q(tick_count[18]));
  FDCE \tick_count_reg[19] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[19]_i_1_n_4 ),
        .Q(tick_count[19]));
  (* ADDER_THRESHOLD = "11" *) 
  CARRY4 \tick_count_reg[19]_i_1 
       (.CI(\tick_count_reg[15]_i_1_n_0 ),
        .CO({\tick_count_reg[19]_i_1_n_0 ,\tick_count_reg[19]_i_1_n_1 ,\tick_count_reg[19]_i_1_n_2 ,\tick_count_reg[19]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\tick_count_reg[19]_i_1_n_4 ,\tick_count_reg[19]_i_1_n_5 ,\tick_count_reg[19]_i_1_n_6 ,\tick_count_reg[19]_i_1_n_7 }),
        .S(tick_count[19:16]));
  FDCE \tick_count_reg[1] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[3]_i_1_n_6 ),
        .Q(tick_count[1]));
  FDCE \tick_count_reg[20] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[23]_i_1_n_7 ),
        .Q(tick_count[20]));
  FDCE \tick_count_reg[21] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[23]_i_1_n_6 ),
        .Q(tick_count[21]));
  FDCE \tick_count_reg[22] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[23]_i_1_n_5 ),
        .Q(tick_count[22]));
  FDCE \tick_count_reg[23] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[23]_i_1_n_4 ),
        .Q(tick_count[23]));
  (* ADDER_THRESHOLD = "11" *) 
  CARRY4 \tick_count_reg[23]_i_1 
       (.CI(\tick_count_reg[19]_i_1_n_0 ),
        .CO({\tick_count_reg[23]_i_1_n_0 ,\tick_count_reg[23]_i_1_n_1 ,\tick_count_reg[23]_i_1_n_2 ,\tick_count_reg[23]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\tick_count_reg[23]_i_1_n_4 ,\tick_count_reg[23]_i_1_n_5 ,\tick_count_reg[23]_i_1_n_6 ,\tick_count_reg[23]_i_1_n_7 }),
        .S(tick_count[23:20]));
  FDCE \tick_count_reg[24] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[27]_i_1_n_7 ),
        .Q(tick_count[24]));
  FDCE \tick_count_reg[25] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[27]_i_1_n_6 ),
        .Q(tick_count[25]));
  FDCE \tick_count_reg[26] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[27]_i_1_n_5 ),
        .Q(tick_count[26]));
  FDCE \tick_count_reg[27] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[27]_i_1_n_4 ),
        .Q(tick_count[27]));
  (* ADDER_THRESHOLD = "11" *) 
  CARRY4 \tick_count_reg[27]_i_1 
       (.CI(\tick_count_reg[23]_i_1_n_0 ),
        .CO({\tick_count_reg[27]_i_1_n_0 ,\tick_count_reg[27]_i_1_n_1 ,\tick_count_reg[27]_i_1_n_2 ,\tick_count_reg[27]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\tick_count_reg[27]_i_1_n_4 ,\tick_count_reg[27]_i_1_n_5 ,\tick_count_reg[27]_i_1_n_6 ,\tick_count_reg[27]_i_1_n_7 }),
        .S(tick_count[27:24]));
  FDCE \tick_count_reg[28] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[31]_i_1_n_7 ),
        .Q(tick_count[28]));
  FDCE \tick_count_reg[29] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[31]_i_1_n_6 ),
        .Q(tick_count[29]));
  FDCE \tick_count_reg[2] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[3]_i_1_n_5 ),
        .Q(tick_count[2]));
  FDCE \tick_count_reg[30] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[31]_i_1_n_5 ),
        .Q(tick_count[30]));
  FDCE \tick_count_reg[31] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[31]_i_1_n_4 ),
        .Q(tick_count[31]));
  (* ADDER_THRESHOLD = "11" *) 
  CARRY4 \tick_count_reg[31]_i_1 
       (.CI(\tick_count_reg[27]_i_1_n_0 ),
        .CO({\NLW_tick_count_reg[31]_i_1_CO_UNCONNECTED [3],\tick_count_reg[31]_i_1_n_1 ,\tick_count_reg[31]_i_1_n_2 ,\tick_count_reg[31]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\tick_count_reg[31]_i_1_n_4 ,\tick_count_reg[31]_i_1_n_5 ,\tick_count_reg[31]_i_1_n_6 ,\tick_count_reg[31]_i_1_n_7 }),
        .S(tick_count[31:28]));
  FDCE \tick_count_reg[3] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[3]_i_1_n_4 ),
        .Q(tick_count[3]));
  (* ADDER_THRESHOLD = "11" *) 
  CARRY4 \tick_count_reg[3]_i_1 
       (.CI(1'b0),
        .CO({\tick_count_reg[3]_i_1_n_0 ,\tick_count_reg[3]_i_1_n_1 ,\tick_count_reg[3]_i_1_n_2 ,\tick_count_reg[3]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b1}),
        .O({\tick_count_reg[3]_i_1_n_4 ,\tick_count_reg[3]_i_1_n_5 ,\tick_count_reg[3]_i_1_n_6 ,\tick_count_reg[3]_i_1_n_7 }),
        .S({tick_count[3:1],\tick_count[3]_i_2_n_0 }));
  FDCE \tick_count_reg[4] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[7]_i_1_n_7 ),
        .Q(tick_count[4]));
  FDCE \tick_count_reg[5] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[7]_i_1_n_6 ),
        .Q(tick_count[5]));
  FDCE \tick_count_reg[6] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[7]_i_1_n_5 ),
        .Q(tick_count[6]));
  FDCE \tick_count_reg[7] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[7]_i_1_n_4 ),
        .Q(tick_count[7]));
  (* ADDER_THRESHOLD = "11" *) 
  CARRY4 \tick_count_reg[7]_i_1 
       (.CI(\tick_count_reg[3]_i_1_n_0 ),
        .CO({\tick_count_reg[7]_i_1_n_0 ,\tick_count_reg[7]_i_1_n_1 ,\tick_count_reg[7]_i_1_n_2 ,\tick_count_reg[7]_i_1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\tick_count_reg[7]_i_1_n_4 ,\tick_count_reg[7]_i_1_n_5 ,\tick_count_reg[7]_i_1_n_6 ,\tick_count_reg[7]_i_1_n_7 }),
        .S(tick_count[7:4]));
  FDCE \tick_count_reg[8] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[11]_i_1_n_7 ),
        .Q(tick_count[8]));
  FDCE \tick_count_reg[9] 
       (.C(clk),
        .CE(tick_count0__0),
        .CLR(\tick_count[31]_i_2_n_0 ),
        .D(\tick_count_reg[11]_i_1_n_6 ),
        .Q(tick_count[9]));
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
