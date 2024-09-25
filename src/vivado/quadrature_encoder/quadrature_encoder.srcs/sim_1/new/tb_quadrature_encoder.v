`timescale 1ms / 1ns

module tb_quadrature_encoder;
    reg clk;
    reg reset;
    reg channelA;
    reg channelB;
    wire direction;
    wire [31:0]tick_count;

    quadrature_encoder uut (
        .clk(clk),
        .reset(reset),
        .channelA(channelA),
        .channelB(channelB),
        .tick_count(tick_count),
        .direction(direction)
    );

  localparam period = 0.001;  //1ns
  localparam GEAR_RATIO = 51;
    // Clock generation

   always
   begin
    clk = 1'b1; #0.0005;  // 0.5ns
    clk = 1'b0; #0.0005;  // 0.5ns
   end

    // Test sequence
    initial begin
        
        // Initialize signals
        reset = 0;
        channelA = 0;
        channelB = 0;

        // Release reset
        #1000 reset = 1;

        repeat ((0.5/(1.25/(1*51)))) begin
            channelA = ~channelA; #((1.25/(1*GEAR_RATIO))*1000); // 1 RPM 
            channelB = ~channelB; #((1.25/(1*GEAR_RATIO))*1000); // 1 RPM 
        end

        repeat ((0.5/(1.25/(2*51)))) begin
            channelA = ~channelA; #((1.25/(2*GEAR_RATIO))*1000); // 2 RPM 
            channelB = ~channelB; #((1.25/(2*GEAR_RATIO))*1000); // 2 RPM 
        end

        repeat ((0.5/(1.25/(3*51)))) begin
            channelA = ~channelA; #((1.25/(3*GEAR_RATIO))*1000); // 3 RPM 
            channelB = ~channelB; #((1.25/(3*GEAR_RATIO))*1000); // 3 RPM 
        end

        repeat ((0.5/(1.25/(10*51)))) begin
            channelB = ~channelB; #((1.25/(10*GEAR_RATIO))*1000); // -10 RPM 
            channelA = ~channelA; #((1.25/(10*GEAR_RATIO))*1000); // -10 RPM 
        end

        repeat ((0.5/(1.25/(123*51)))) begin
            channelB = ~channelB; #((1.25/(123*GEAR_RATIO))*1000); // -123 RPM 
            channelA = ~channelA; #((1.25/(123*GEAR_RATIO))*1000); // -123 RPM 
        end

        repeat ((0.5/(1.25/(89*51)))) begin
            channelB = ~channelB; #((1.25/(89*GEAR_RATIO))*1000); // -89 RPM 
            channelA = ~channelA; #((1.25/(89*GEAR_RATIO))*1000); // -89 RPM 
        end
        
        repeat ((0.5/(1.25/(186*GEAR_RATIO)))) begin
            channelA = ~channelA; #((1.25/(186*GEAR_RATIO))*1000); // 186 RPM 
            channelB = ~channelB; #((1.25/(186*GEAR_RATIO))*1000); // 186 RPM 
        end
        
        // Stop simulation
        $display("fine");
        $stop; 
    end
endmodule

