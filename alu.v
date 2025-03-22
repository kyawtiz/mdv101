module ALU (
    input wire carry_in,
    input wire [15:0] in_a,
    input wire [15:0] in_b,
    input wire [3:0] select,
    input wire mode,
    output wire carry_out,
    output wire compare,
    output wire [15:0] alu_out
);

wire [15:0] arith_out, logic_out;
wire arith_carry, arith_compare;

ArithmeticUnit arith_unit (
    .carry_in(carry_in),
    .in_a(in_a),
    .in_b(in_b),
    .select(select),
    .carry_out(arith_carry),
    .compare(arith_compare),
    .arith_out(arith_out)
);

LogicUnit logic_unit (
    .in_a(in_a),
    .in_b(in_b),
    .select(select),
    .logic_out(logic_out)
);

assign alu_out = mode ? logic_out : arith_out;
assign carry_out = mode ? 1'b0 : arith_carry;
assign compare = mode ? 1'b0 : arith_compare;

endmodule

module ArithmeticUnit (
    input wire carry_in,
    input wire [15:0] in_a,
    input wire [15:0] in_b,
    input wire [3:0] select,
    output reg carry_out,
    output reg compare,
    output reg [15:0] arith_out
);

always @(*) begin
    case (select)
        // Key fix: Extend carry_in to 17 bits using concatenation
        4'b0000: {carry_out, arith_out} = in_a + in_b + {16'b0, carry_in}; // Add with carry
        4'b0001: {carry_out, arith_out} = in_a - in_b - {16'b0, carry_in}; // Subtract with borrow
        4'b0010: {carry_out, arith_out} = in_a + in_b;                    // Normal add
        4'b0011: {carry_out, arith_out} = in_a - in_b;                    // Normal subtract
        default: {carry_out, arith_out} = {1'b0, 16'b0};
    endcase
    compare = (arith_out == 16'b0); // Compare flag
end

endmodule

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
