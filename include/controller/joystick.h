#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "pins.h"
#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int16_t center_x;
    int16_t center_y;
    uint8_t deadzone;
} joystick_t;

void joystick_init(joystick_t* joy);
void joystick_setup(joystick_t* joy);
void joystick_calibrate(joystick_t* joy);
uint8_t joystick_read_x(joystick_t* joy);
uint8_t joystick_read_y(joystick_t* joy);
uint8_t joystick_read_button(joystick_t* joy);
uint8_t joystick_read_button(joystick_t* joy);

#ifdef __cplusplus
}
#endif

#endif