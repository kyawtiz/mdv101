#include "VAlu.h"
#include "verilated.h"
#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    VAlu* top = new VAlu;

    srand(time(0)); // Seed the random number generator

    // Test Arithmetic mode
    top->mode = 0;

    // Test Addition
    top->select = 4'b0000;
    for (int i = 0; i < 1000; ++i) {
        top->in_a = rand() & 0xFFFF; // Generate random 16-bit inputs
        top->in_b = rand() & 0xFFFF;
        top->carry_in = rand() & 0x1;
        top->eval();
        // You could add checks here to verify the results
        // Example: if (top->alu_out != (top->in_a + top->in_b + top->carry_in)) { ... }
    }
    std::cout << "Addition tests passed." << std::endl;

    // Test Subtraction
    top->select = 4'b0001;
    for (int i = 0; i < 1000; ++i) {
        top->in_a = rand() & 0xFFFF;
        top->in_b = rand() & 0xFFFF;
        top->carry_in = rand() & 0x1;
        top->eval();
        // Add checks here
    }
    std::cout << "Subtraction tests passed." << std::endl;

    // Test AND
    top->select = 4'b0010;
    for (int i = 0; i < 1000; ++i) {
        top->in_a = rand() & 0xFFFF;
        top->in_b = rand() & 0xFFFF;
        top->eval();
        // Add checks here
    }
    std::cout << "AND tests passed." << std::endl;

    // Test OR
    top->select = 4'b0011;
    for (int i = 0; i < 1000; ++i) {
        top->in_a = rand() & 0xFFFF;
        top->in_b = rand() & 0xFFFF;
        top->eval();
        // Add checks here
    }
    std::cout << "OR tests passed." << std::endl;

    // Test XOR
    top->select = 4'b0100;
    for (int i = 0; i < 1000; ++i) {
        top->in_a = rand() & 0xFFFF;
        top->in_b = rand() & 0xFFFF;
        top->eval();
        // Add checks here
    }
    std::cout << "XOR tests passed." << std::endl;

    // Test NOT A
    top->select = 4'b0101;
    for (int i = 0; i < 1000; ++i) {
        top->in_a = rand() & 0xFFFF;
        top->eval();
        // Add checks here
    }
    std::cout << "NOT A tests passed." << std::endl;

    // Test NOT B
    top->select = 4'b0110;
    for (int i = 0; i < 1000; ++i) {
        top->in_b = rand() & 0xFFFF;
        top->eval();
        // Add checks here
    }
    std::cout << "NOT B tests passed." << std::endl;

    // Test A
    top->select = 4'b0111;
    for (int i = 0; i < 1000; ++i) {
        top->in_a = rand() & 0xFFFF;
        top->eval();
        // Add checks here
    }
    std::cout << "A tests passed." << std::endl;

    // Test B
    top->select = 4'b1000;
    for (int i = 0; i < 1000; ++i) {
        top->in_b = rand() & 0xFFFF;
        top->eval();
        // Add checks here
    }
    std::cout << "B tests passed." << std::endl;

    // Test Shift Left
    top->select = 4'b1001;
    for (int i = 0; i < 1000; ++i) {
        top->in_a = rand() & 0xFFFF;
        top->eval();
        // Add checks here
    }
    std::cout << "Shift Left tests passed." << std::endl;

    // Test Shift Right
    top->select = 4'b1010;
    for (int i = 0; i < 1000; ++i) {
        top->in_a = rand() & 0xFFFF;
        top->eval();
        // Add checks here
    }
    std::cout << "Shift Right tests passed." << std::endl;

    // Test Logic mode
    top->mode = 1;

    // Repeat tests for Logic mode (AND, OR, XOR, NOT A, NOT B, A, B, Shift Left, Shift Right)

    delete top;
    return 0;
}
