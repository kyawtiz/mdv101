#include <iostream>
#include <random>
#include <bitset>
using namespace std;

// Model of the Logic Unit
uint16_t LogicUnitModel(uint16_t a, uint16_t b, uint8_t sel) {
    switch (sel) {
        case 0x0: return a & b;
        case 0x1: return a | b;
        case 0x2: return a ^ b;
        case 0x3: return ~a;
        case 0x4: return ~b;
        case 0x5: return a;
        case 0x6: return b;
        case 0x7: return a << 1;
        case 0x8: return a >> 1;
        default: return 0;
    }
}

// Model of the Arithmetic Unit
void ArithmeticUnitModel(uint16_t cin, uint16_t a, uint16_t b, uint8_t sel, 
                         uint16_t &out, uint16_t &cout, uint16_t &cmp) {
    uint32_t res;
    switch (sel) {
        case 0x0: res = a + b; break;
        case 0x1: res = a - b; break;
        case 0x2: res = a + b + cin; break;
        case 0x3: res = a - b - cin; break;
        default: res = 0;
    }
    out = res & 0xFFFF;
    cout = (res >> 16) & 1;
    cmp = (out == 0) ? 1 : 0;
}

// ALU Model
void ALUModel(uint16_t cin, uint16_t a, uint16_t b, uint8_t sel, bool mode,
              uint16_t &out, uint16_t &cout, uint16_t &cmp) {
    if (mode) { // Logic mode
        out = LogicUnitModel(a, b, sel);
        cout = 0;
        cmp = 0;
    } else {    // Arithmetic mode
        ArithmeticUnitModel(cin, a, b, sel, out, cout, cmp);
    }
}

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<uint16_t> data_dist(0, 0xFFFF);
    uniform_int_distribution<uint8_t> carry_dist(0, 1);

    // Test each arithmetic operation (4 operations)
    for (int op = 0; op < 4; op++) {
        for (int i = 0; i < 1000; i++) {
            uint16_t a = data_dist(gen);
            uint16_t b = data_dist(gen);
            uint16_t cin = carry_dist(gen);
            uint16_t out, cout, cmp;

            ALUModel(cin, a, b, op, 0, out, cout, cmp);

            // Verify against model
            uint16_t exp_out, exp_cout, exp_cmp;
            ArithmeticUnitModel(cin, a, b, op, exp_out, exp_cout, exp_cmp);

            if (out != exp_out || cout != exp_cout || cmp != exp_cmp) {
                cerr << "Arithmetic Test Failed: Op=" << op 
                     << " A=" << a << " B=" << b << " Cin=" << cin << endl;
                return 1;
            }
        }
    }

    // Test each logic operation (9 operations)
    for (int op = 0; op <= 8; op++) {
        for (int i = 0; i < 1000; i++) {
            uint16_t a = data_dist(gen);
            uint16_t b = data_dist(gen);
            uint16_t out, cout, cmp;

            ALUModel(0, a, b, op, 1, out, cout, cmp);

            // Verify against model
            uint16_t exp_out = LogicUnitModel(a, b, op);
            if (out != exp_out || cout != 0 || cmp != 0) {
                cerr << "Logic Test Failed: Op=" << op 
                     << " A=" << a << " B=" << b << endl;
                return 1;
            }
        }
    }

    cout << "All tests passed successfully!" << endl;
    return 0;
}
