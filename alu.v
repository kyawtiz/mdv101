module alu (
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

