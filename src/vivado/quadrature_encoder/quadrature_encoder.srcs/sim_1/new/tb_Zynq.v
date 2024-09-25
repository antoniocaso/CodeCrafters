`timescale 1ns / 1ns

module tb_Zynq(); 
    reg tb_ACLK;   // PS clock 
    reg tb_ARESETn; // PS reset 
    wire temp_clk; 
    wire temp_rstn;  
    // Signals received from the AXI interface 
    reg [31:0] read_data1; 
    reg [31:0] read_data2; 
    reg resp; 
    //    SWITCHES  
    reg channelA;
    reg channelB;   // reg, will be defined in the initial block 
    // IP output 
    wire [31:0]tick_count;
    wire direction; 
    localparam period=5;    
    // GPIO IP registers 
    // simulate with a 200MHz clock. FCLK0 is 50Mhz. 
    localparam IPbaseaddress=32'h4120_0000;     
    localparam GPIO_DATA1=IPbaseaddress+4'h0;   // data register channel 1 
    localparam GPIO_DATA2=IPbaseaddress+32'h0001_0000+4'h0;
    localparam GPIO_TRI1=IPbaseaddress+4'h4;  
    localparam GPIO_TRI2=IPbaseaddress+32'h0001_0000+4'h4;
    always     
    begin  
        // Clock Generator at 200MHz 
        tb_ACLK = 1'b0;#(period/2.0); 
        tb_ACLK = 1'b1;#(period/2.0); 
    end 
    assign temp_clk=tb_ACLK; 
    assign temp_rstn=tb_ARESETn;  
    // state register channel 1 
    assign tick_count = read_data1; // Pick the bit 0 of the data for visualization purposes
    assign direction = read_data2[0];
    // The SoC that is tested clock, reset and the switches are connected 
     
    design_1_wrapper UUT 
    (.DDR_addr(),.DDR_ba(),.DDR_cas_n(),.DDR_ck_n(),.DDR_ck_p(),.DDR_cke(),.DDR_cs_n(),.DDR_dm(), 
    .DDR_dq(),.DDR_dqs_n(),.DDR_dqs_p(),.DDR_odt(),.DDR_ras_n(),.DDR_reset_n(),.DDR_we_n(), 
    .FIXED_IO_ddr_vrn(),.FIXED_IO_ddr_vrp(),.FIXED_IO_mio(),.FIXED_IO_ps_clk(temp_clk), 
    .FIXED_IO_ps_porb(temp_rstn),.FIXED_IO_ps_srstb(temp_rstn), .channelA(channelA), .channelB(channelB)); 
   
    initial 
    begin 
        //SW=2'b00; tb_ARESETn = 1'b0;#(20*period);  
        //SW=2'b00; tb_ARESETn = 1'b1;#(10*period); 
        channelA = 0;
        channelB = 0;
        tb_ARESETn = 1'b0;#(20*period);
        
        channelA = 0;
        channelB = 0;
        tb_ARESETn = 1'b1;#(10*period);

        //Reset the PL 
        UUT.design_1_i.processing_system7_0.inst.fpga_soft_reset(32'h1); 
        UUT.design_1_i.processing_system7_0.inst.fpga_soft_reset(32'h0);#(10*period); 
        
        UUT.design_1_i.processing_system7_0.inst.read_data(GPIO_DATA1,4,read_data1, resp);#period; 
        UUT.design_1_i.processing_system7_0.inst.read_data(GPIO_DATA2,4,read_data2, resp);#(5*period);
        
    
        repeat (6) begin
            channelA = ~channelA; #((1.25/(191.0*51.0))*1000000000); // 186 RPM 
            channelB = ~channelB; #((1.25/(191.0*51.0))*1000000000); // 186 RPM 
        end 
        UUT.design_1_i.processing_system7_0.inst.read_data(GPIO_DATA1,4,read_data1, resp);#period; 
        UUT.design_1_i.processing_system7_0.inst.read_data(GPIO_DATA2,4,read_data2, resp);#(5*period);
        
        
        #2;


    $stop; 
    end 
endmodule 