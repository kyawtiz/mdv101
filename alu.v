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
            4'b0000: begin // Addition
                arith_out = in_a + in_b + carry_in;
                carry_out = (in_a + in_b + carry_in) > 16'hFFFF;
                compare = (in_a + in_b + carry_in) == 0;
            end
            4'b0001: begin // Subtraction
                arith_out = in_a - in_b - carry_in;
                carry_out = (in_a - in_b - carry_in) < 0;
                compare = (in_a - in_b - carry_in) == 0;
            end
            4'b0010: begin // AND
                arith_out = in_a & in_b;
                carry_out = 1'b0;
                compare = (in_a & in_b) == 0;
            end
            4'b0011: begin // OR
                arith_out = in_a | in_b;
                carry_out = 1'b0;
                compare = (in_a | in_b) == 0;
            end
            4'b0100: begin // XOR
                arith_out = in_a ^ in_b;
                carry_out = 1'b0;
                compare = (in_a ^ in_b) == 0;
            end
            4'b0101: begin // NOT A
                arith_out = ~in_a;
                carry_out = 1'b0;
                compare = (~in_a) == 0;
            end
            4'b0110: begin // NOT B
                arith_out = ~in_b;
                carry_out = 1'b0;
                compare = (~in_b) == 0;
            end
            4'b0111: begin // A
                arith_out = in_a;
                carry_out = 1'b0;
                compare = (in_a) == 0;
            end
            4'b1000: begin // B
                arith_out = in_b;
                carry_out = 1'b0;
                compare = (in_b) == 0;
            end
            4'b1001: begin // Shift Left
                arith_out = in_a << 1;
                carry_out = 1'b0;
                compare = (in_a << 1) == 0;
            end
            4'b1010: begin // Shift Right
                arith_out = in_a >> 1;
                carry_out = 1'b0;
                compare = (in_a >> 1) == 0;
            end
            default: begin
                arith_out = 16'h0000;
                carry_out = 1'b0;
                compare = 1'b0;
            end
        endcase
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
            4'b0000: logic_out = in_a & in_b;
            4'b0001: logic_out = in_a | in_b;
            4'b0010: logic_out = in_a ^ in_b;
            4'b0011: logic_out = ~in_a;
            4'b0100: logic_out = ~in_b;
            4'b0101: logic_out = in_a;
            4'b0110: logic_out = in_b;
            4'b0111: logic_out = in_a << 1;
            4'b1000: logic_out = in_a >> 1;
            default: logic_out = 16'h0000;
        endcase
    end

endmodule

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

    wire [15:0] arith_out;
    wire arith_carry_out;
    wire arith_compare;
    wire [15:0] logic_out;

    ArithmeticUnit arith_unit (
        .carry_in(carry_in),
        .in_a(in_a),
        .in_b(in_b),
        .select(select),
        .carry_out(arith_carry_out),
        .compare(arith_compare),
        .arith_out(arith_out)
    );

    LogicUnit logic_unit (
        .in_a(in_a),
        .in_b(in_b),
        .select(select),
        .logic_out(logic_out)
    );

    assign carry_out = arith_carry_out;
    assign compare = arith_compare;
    assign alu_out = mode ? logic_out : arith_out;

endmodule
