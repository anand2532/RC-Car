#include "motor.h"
#include "Arduino.h"

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

static uint8_t get_speed_multiplier(speed_mode_t mode) {
    switch (mode) {
        case SPEED_SLOW: return 25;
        case SPEED_NORMAL: return 50;
        case SPEED_FAST: return 75;
        case SPEED_TURBO: return 100;
        default: return 50;
    }
}

void motor_drive(motor_t* motor, uint8_t x, uint8_t y) {
    int16_t forward = ((int16_t)y * 2) - 255;
    int16_t turn = ((int16_t)x * 2) - 255;
    
    int16_t left_speed = forward + turn;
    int16_t right_speed = forward - turn;
    
    uint8_t multiplier = get_speed_multiplier(motor->speed_mode);
    left_speed = (left_speed * multiplier) / 100;
    right_speed = (right_speed * multiplier) / 100;
    
    // Left motor
    if (left_speed > 0) {
        digitalWrite(LEFT_MOTOR_PIN1, HIGH);
        digitalWrite(LEFT_MOTOR_PIN2, LOW);
    } else {
        digitalWrite(LEFT_MOTOR_PIN1, LOW);
        digitalWrite(LEFT_MOTOR_PIN2, HIGH);
        left_speed = -left_speed;
    }
    analogWrite(LEFT_ENABLE_PIN, left_speed > 255 ? 255 : left_speed);
    
    // Right motor
    if (right_speed > 0) {
        digitalWrite(RIGHT_MOTOR_PIN1, HIGH);
        digitalWrite(RIGHT_MOTOR_PIN2, LOW);
    } else {
        digitalWrite(RIGHT_MOTOR_PIN1, LOW);
        digitalWrite(RIGHT_MOTOR_PIN2, HIGH);
        right_speed = -right_speed;
    }
    analogWrite(RIGHT_ENABLE_PIN, right_speed > 255 ? 255 : right_speed);
}

void motor_toggle_speed(motor_t* motor) {
    motor->speed_mode = (speed_mode_t)((motor->speed_mode + 1) % 4);
}
