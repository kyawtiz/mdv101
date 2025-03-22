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
        4'b0000: {carry_out, arith_out} = in_a + in_b;          // Add
        4'b0001: {carry_out, arith_out} = in_a - in_b;          // Subtract
        4'b0010: {carry_out, arith_out} = in_a + in_b + carry_in; // Add with carry
        4'b0011: {carry_out, arith_out} = in_a - in_b - carry_in; // Subtract with borrow
        default: {carry_out, arith_out} = {1'b0, 16'b0};
    endcase
    compare = (arith_out == 16'b0); // Compare flag
end

endmodule
