#include "joystick.h"


void joystick_init(joystick_t* joy) {
    joy->deadzone = 10;
    joy->center_x = 255;
    joy->center_y = 255;
}

void joystick_setup(joystick_t joy) {
    pinMode(JOYSTICK_BTN_PIN, INPUT_PULLUP);
    analogReadResolution(12);                  // 12 bit resolution for SAMD21
}

void joystick_calibration(joystick_t* joy) {
    long sum_x = 0;
    long sum_y = 0;
    const int samples = 10;

    for (int i = 0; i < samples; i++) {
        sum_x += analogRead(JOYSTICK_X_PIN);
        sum_y += analogRead(JOYSTICK_Y_PIN);
        delay(10);
    }

    joy->center_x = sum_x / samples;
    joy->center_y = sum_y / samples;
}

uint8_t joystick_read_x(joystick_t* joy) {
    int32_t raw = analogRead(JOYSTICK_X_PIN);
    int32_t centered = raw - joy->center_x;

    if (abs(centered) < joy->center_x) {
        return 128;
    }

    return constrain(map(centered, -2048, 2047, 0, 255), 0, 255);
}

uint8_t joystick_read_y(joystick_t* joy) {
    int32_t raw = analogRead(JOYSTICK_Y_PIN);
    int32_t centered = raw - joy->center_y;

    if (abs(centered) < joy->center_y) {
        return 128;
    }

    return constrain(map(centered, -2048, 2047, 0, 255), 0, 255);
}

uint8_t joystick_read_button(joystick_t* joy) {
    return !digitalRead(JOYSTICK_BTN_PIN);          // Active Low
}

