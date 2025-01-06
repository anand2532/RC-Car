#include <unity.h>
#include "motor.h"
#include <string.h>

// Test state
static struct {
    uint8_t pin_modes[20];
    uint8_t digital_values[20];
    uint8_t analog_values[20];
} test_state;

// Mock Arduino functions
void digitalWrite(uint8_t pin, uint8_t val) {
    test_state.digital_values[pin] = val;
}

void analogWrite(uint8_t pin, int val) {
    test_state.analog_values[pin] = val;
}

void pinMode(uint8_t pin, uint8_t mode) {
    test_state.pin_modes[pin] = mode;
}

// Unity setUp and tearDown
void setUp(void) {
    memset(&test_state, 0, sizeof(test_state));
}

void tearDown(void) {
}

// Test Functions
void test_motor_init(void) {
    motor_t motor;
    motor_init(&motor);
    TEST_ASSERT_EQUAL(SPEED_NORMAL, motor.speed_mode);
}

void test_motor_setup(void) {
    motor_t motor;
    motor_init(&motor);
    motor_setup(&motor);
    
    TEST_ASSERT_EQUAL(OUTPUT, test_state.pin_modes[LEFT_MOTOR_PIN1]);
    TEST_ASSERT_EQUAL(OUTPUT, test_state.pin_modes[LEFT_MOTOR_PIN2]);
    TEST_ASSERT_EQUAL(OUTPUT, test_state.pin_modes[RIGHT_MOTOR_PIN1]);
    TEST_ASSERT_EQUAL(OUTPUT, test_state.pin_modes[RIGHT_MOTOR_PIN2]);
}

void test_motor_forward(void) {
    motor_t motor;
    motor_init(&motor);
    motor_setup(&motor);
    
    // Test forward motion
    motor_drive(&motor, 128, 255);
    
    // Check directions
    TEST_ASSERT_EQUAL(HIGH, test_state.digital_values[LEFT_MOTOR_PIN1]);
    TEST_ASSERT_EQUAL(LOW, test_state.digital_values[LEFT_MOTOR_PIN2]);
    TEST_ASSERT_EQUAL(HIGH, test_state.digital_values[RIGHT_MOTOR_PIN1]);
    TEST_ASSERT_EQUAL(LOW, test_state.digital_values[RIGHT_MOTOR_PIN2]);
}

void test_motor_backward(void) {
    motor_t motor;
    motor_init(&motor);
    motor_setup(&motor);
    
    // Test backward motion
    motor_drive(&motor, 128, 0);
    
    // Check directions are reversed
    TEST_ASSERT_EQUAL(LOW, test_state.digital_values[LEFT_MOTOR_PIN1]);
    TEST_ASSERT_EQUAL(HIGH, test_state.digital_values[LEFT_MOTOR_PIN2]);
    TEST_ASSERT_EQUAL(LOW, test_state.digital_values[RIGHT_MOTOR_PIN1]);
    TEST_ASSERT_EQUAL(HIGH, test_state.digital_values[RIGHT_MOTOR_PIN2]);
}

void test_motor_speed_modes(void) {
    motor_t motor;
    motor_init(&motor);
    
    // Test all speed modes
    speed_mode_t modes[] = {SPEED_NORMAL, SPEED_FAST, SPEED_TURBO, SPEED_SLOW};
    
    for(int i = 0; i < 4; i++) {
        speed_mode_t initial_mode = motor.speed_mode;
        motor_toggle_speed(&motor);
        TEST_ASSERT_EQUAL(modes[(i + 1) % 4], motor.speed_mode);
    }
}

void setup() {
    UNITY_BEGIN();
    
    RUN_TEST(test_motor_init);
    RUN_TEST(test_motor_setup);
    RUN_TEST(test_motor_forward);
    RUN_TEST(test_motor_backward);
    RUN_TEST(test_motor_speed_modes);
    
    UNITY_END();
}

void loop() {
}

// For native testing
int main(int argc, char **argv) {
    setup();
    return 0;
}