#include "motor.h"

const uint8_t LEFT_MOTOR_PIN1 = 11;
const uint8_t LEFT_MOTOR_PIN2 = 12;
const uint8_t RIGHT_MOTOR_PIN1 = 9;
const uint8_t RIGHT_MOTOR_PIN2 = 10;
const uint8_t LEFT_ENABLE_PIN = 5;
const uint8_t RIGHT_ENABLE_PIN = 6;

static uint8_t get_speed_multiplier(speed_mode_t mode) {
    const uint8_t multipliers[] = {25, 50, 75, 100};
    return multipliers[mode];
}

static void set_motor_speed(uint8_t enable_pin, uint8_t pin1, uint8_t pin2, int16_t speed) {
    if (speed > 0) {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
    } else {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        speed = -speed;
    }
    analogWrite(enable_pin, speed > 255 ? 255 : speed);
}

void motor_init(motor_t* motor) {
    motor->speed_mode = SPEED_NORMAL;
}

void motor_setup(motor_t* motor) {
    pinMode(LEFT_MOTOR_PIN1, OUTPUT);
    pinMode(LEFT_MOTOR_PIN2, OUTPUT);
    pinMode(RIGHT_MOTOR_PIN1, OUTPUT);
    pinMode(RIGHT_MOTOR_PIN2, OUTPUT);
    pinMode(LEFT_ENABLE_PIN, OUTPUT);
    pinMode(RIGHT_ENABLE_PIN, OUTPUT);
}

void motor_drive(motor_t* motor, uint8_t x, uint8_t y) {
    int16_t forward = ((int16_t)y * 2) - 255;
    int16_t turn = ((int16_t)x * 2) - 255;
    
    int16_t left_speed = forward + turn;
    int16_t right_speed = forward - turn;
    
    uint8_t multiplier = get_speed_multiplier(motor->speed_mode);
    left_speed = (left_speed * multiplier) / 100;
    right_speed = (right_speed * multiplier) / 100;
    
    set_motor_speed(LEFT_ENABLE_PIN, LEFT_MOTOR_PIN1, LEFT_MOTOR_PIN2, left_speed);
    set_motor_speed(RIGHT_ENABLE_PIN, RIGHT_MOTOR_PIN1, RIGHT_MOTOR_PIN2, right_speed);
}

void motor_toggle_speed(motor_t* motor) {
    motor->speed_mode = static_cast<speed_mode_t>((static_cast<int>(motor->speed_mode) + 1) % 4);
}