module key_lock_system (
    input clk,
    input reset,
    input [3:0] key_in,  // 4-bit key input
    output reg locked    // Lock status (1: Locked, 0: Unlocked)
);

    // State encoding
    localparam  LOCKED = 3'b000,
                STATE1 = 3'b001,
                STATE2 = 3'b010,
                STATE3 = 3'b011,
                STATE4 = 3'b100,
                STATE5 = 3'b101,
                UNLOCKED = 3'b110;

    reg [2:0] current_state, next_state;

    // State register (sequential logic)
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            current_state <= LOCKED;
        end else begin
            current_state <= next_state;
        end
    end

    // Next state decode logic (combinational logic)
    always @(*) begin
        case (current_state)
            LOCKED:  if (key_in == 4'd3) next_state = STATE1; else next_state = LOCKED;
            STATE1:  if (key_in == 4'd3) next_state = STATE2; else next_state = LOCKED;
            STATE2:  if (key_in == 4'd5) next_state = STATE3; else next_state = LOCKED;
            STATE3:  if (key_in == 4'd2) next_state = STATE4; else next_state = LOCKED;
            STATE4:  if (key_in == 4'd5) next_state = STATE5; else next_state = LOCKED;
            STATE5:  if (key_in == 4'd6) next_state = UNLOCKED; else next_state = LOCKED;
            UNLOCKED: next_state = UNLOCKED;  // Stay in unlocked state
            default: next_state = LOCKED;
        endcase
    end

    // Output logic (combinational logic)
    always @(*) begin
        if (current_state == UNLOCKED) begin
            locked = 0;  // Unlocked
        end else begin
            locked = 1;  // Locked
        end
    end
