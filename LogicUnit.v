module LogicUnit (
    input wire [15:0] in_a,
    input wire [15:0] in_b,
    input wire [3:0] select,
    output reg [15:0] logic_out
);

always @(*) begin
    case (select)
        4'b0000: logic_out = in_a & in_b;    // AND
        4'b0001: logic_out = in_a | in_b;    // OR
        4'b0010: logic_out = in_a ^ in_b;    // XOR
        4'b0011: logic_out = ~in_a;          // NOT A
        4'b0100: logic_out = ~in_b;          // NOT B
        4'b0101: logic_out = in_a;           // Pass A
        4'b0110: logic_out = in_b;           // Pass B
        4'b0111: logic_out = in_a << 1;      // Shift left
        4'b1000: logic_out = in_a >> 1;      // Shift right
        default: logic_out = 16'b0;
    endcase
end

endmodule
