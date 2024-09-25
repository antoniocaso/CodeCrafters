module quadrature_encoder(
    input wire clk,           // clock signal
    input wire reset,         // reset signal
    input wire channelA,      // quadrature encoder channel A
    input wire channelB,      // quadrature encoder channel B
    output reg [31:0]tick_count, //ever increasing number of ticks 
    output reg direction      // direction of rotation: 0 - clockwise, 1 - counter-clockwise
);
    reg [2:0] channelA_delayed, channelB_delayed;

    always @(posedge clk or negedge reset) begin
    
        if (reset == 1'b0) begin
        
              tick_count <= 32'd0;
              direction <= 1'b0;
              channelA_delayed <= 3'b000;
              channelB_delayed <= 3'b000;
              
        end else begin

              if (channelA_delayed[1] ^ channelA_delayed[2] ^ channelB_delayed[1] ^ channelB_delayed[2]) begin
                  if(channelA_delayed[1] ^ channelB_delayed[2]) direction <= 1'b1;
                  else direction <= 1'b0;
                  tick_count <= tick_count + 1;
              end
          
        channelA_delayed <= {channelA_delayed[1:0], channelA};
        channelB_delayed <= {channelB_delayed[1:0], channelB};

        end
  end
endmodule
