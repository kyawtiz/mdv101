module LogicUnit (
    input wire [15:0] in_a,
    input wire [15:0] in_b,
    input wire [3:0] select,
    output reg [15:0] out
);

    always @(*) begin
        case (select)
            4'b0000: out = ~in_a;              
            4'b0001: out = ~(in_a | in_b);     
            4'b0010: out = ~in_a & in_b;       
            4'b0011: out = 16'b0000_0000_0000_0000; // Logical 0
            4'b0100: out = ~(in_a & in_b);    
            4'b0101: out = ~in_b;              
            4'b0110: out = in_a ^ in_b;        
            4'b0111: out = in_a & ~in_b;       
            4'b1000: out = ~in_a | in_b;       
            4'b1001: out = ~(in_a ^ in_b);    
            4'b1010: out = in_b;               
            4'b1011: out = in_a & in_b;        
            4'b1100: out = 16'b1111_1111_1111_1111; // Logical 1
            4'b1101: out = in_a | ~in_b;       
            4'b1110: out = in_a | in_b;        
            4'b1111: out = in_a;              
            default: out = 16'b0000_0000_0000_0000;
        endcase
    end

endmodule
