#include <iostream>
#include <vector>
#include <cassert>

// Define the states as enums for better readability
enum State {
    LOCKED,
    STATE1,
    STATE2,
    STATE3,
    STATE4,
    STATE5,
    UNLOCKED
};

class KeyLock {
public:
    KeyLock() : current_state_(LOCKED), locked_(true) {}

    void reset() {
        current_state_ = LOCKED;
        locked_ = true;
    }

    void set_key_in(int key) {
        key_in_ = key & 0x0F; // Ensure only 4 bits are considered
    }

    void clock_tick() {
        next_state_ = current_state_; // Default to staying in the current state

        switch (current_state_) {
            case LOCKED:
                if (key_in_ == 3) next_state_ = STATE1;
                else next_state_ = LOCKED;
                break;
            case STATE1:
                if (key_in_ == 3) next_state_ = STATE2;
                else next_state_ = LOCKED;
                break;
            case STATE2:
                if (key_in_ == 5) next_state_ = STATE3;
                else next_state_ = LOCKED;
                break;
            case STATE3:
                if (key_in_ == 2) next_state_ = STATE4;
                else next_state_ = LOCKED;
                break;
            case STATE4:
                if (key_in_ == 5) next_state_ = STATE5;
                else next_state_ = LOCKED;
                break;
            case STATE5:
                if (key_in_ == 6) next_state_ = UNLOCKED;
                else next_state_ = LOCKED;
                break;
            case UNLOCKED:
                next_state_ = UNLOCKED;
                break;
            default:
                next_state_ = LOCKED;
                break;
        }

        current_state_ = next_state_;
        locked_ = (current_state_ != UNLOCKED);
    }

    bool is_locked() const {
        return locked_;
    }

    State get_current_state() const {
        return current_state_;
    }

private:
    State current_state_;
    State next_state_;
    int key_in_;
    bool locked_;
};

int main() {
    KeyLock lock;

    std::cout << "Starting Test Bench for key_lock module..." << std::endl;

    // Test Case 1: Initial state should be locked
    std::cout << "Test Case 1: Initial state..." << std::endl;
    assert(lock.is_locked() == true);
    std::cout << "  Initial state is LOCKED (as expected)." << std::endl;

    // Test Case 2: Resetting the module
    std::cout << "\nTest Case 2: Resetting the module..." << std::endl;
    lock.reset();
    assert(lock.is_locked() == true);
    std::cout << "  Module reset successfully to LOCKED state." << std::endl;

    // Test Case 3: Entering the correct key sequence
    std::cout << "\nTest Case 3: Entering the correct key sequence (3, 3, 5, 2, 5, 6)..." << std::endl;

    lock.set_key_in(3);
    lock.clock_tick();
    assert(lock.get_current_state() == STATE1);
    std::cout << "  Entered 3, state is now STATE1." << std::endl;
    assert(lock.is_locked() == true);

    lock.set_key_in(3);
    lock.clock_tick();
    assert(lock.get_current_state() == STATE2);
    std::cout << "  Entered 3, state is now STATE2." << std::endl;
    assert(lock.is_locked() == true);

    lock.set_key_in(5);
    lock.clock_tick();
    assert(lock.get_current_state() == STATE3);
    std::cout << "  Entered 5, state is now STATE3." << std::endl;
    assert(lock.is_locked() == true);

    lock.set_key_in(2);
    lock.clock_tick();
    assert(lock.get_current_state() == STATE4);
    std::cout << "  Entered 2, state is now STATE4." << std::endl;
    assert(lock.is_locked() == true);

    lock.set_key_in(5);
    lock.clock_tick();
    assert(lock.get_current_state() == STATE5);
    std::cout << "  Entered 5, state is now STATE5." << std::endl;
    assert(lock.is_locked() == true);

    lock.set_key_in(6);
    lock.clock_tick();
    assert(lock.get_current_state() == UNLOCKED);
    std::cout << "  Entered 6, state is now UNLOCKED." << std::endl;
    assert(lock.is_locked() == false);
    std::cout << "  Lock is now UNLOCKED (as expected)." << std::endl;

    // Test Case 4: Staying in the unlocked state
    std::cout << "\nTest Case 4: Staying in the unlocked state..." << std::endl;
    lock.set_key_in(9); // Entering a wrong key
    lock.clock_tick();
    assert(lock.get_current_state() == UNLOCKED);
    assert(lock.is_locked() == false);
    std::cout << "  Entered wrong key, still in UNLOCKED state." << std::endl;

    // Test Case 5: Entering an incorrect key at the beginning
    std::cout << "\nTest Case 5: Entering an incorrect key at the beginning..." << std::endl;
    lock.reset();
    lock.set_key_in(5); // Incorrect first key
    lock.clock_tick();
    assert(lock.get_current_state() == LOCKED);
    assert(lock.is_locked() == true);
    std::cout << "  Entered wrong first key, back to LOCKED state." << std::endl;

    // Test Case 6: Entering an incorrect key in the middle of the sequence
    std::cout << "\nTest Case 6: Entering an incorrect key in the middle of the sequence..." << std::endl;
    lock.reset();
    lock.set_key_in(3);
    lock.clock_tick();
    lock.set_key_in(3);
    lock.clock_tick();
    lock.set_key_in(7); // Incorrect key
    lock.clock_tick();
    assert(lock.get_current_state() == LOCKED);
    assert(lock.is_locked() == true);
    std::cout << "  Entered wrong key in the middle, back to LOCKED state." << std::endl;

    std::cout << "\nAll test cases completed successfully!" << std::endl;

    return 0;
}
