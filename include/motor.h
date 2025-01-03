#ifndef MOTOR_H
#define MOTOR_H

#include "common.h"

typedef enum {
    SPEED_SLOW = 0,
    SPEED_NORMAL,
    SPEED_FAST,
    SPEED_TURBO
} speed_mode_t;

typedef struct {
    speed_mode_t speed_mode;
} motor_t;

void motor_init(motor_t* motor);
void motor_setup(motor_t* motor);
void motor_drive(motor_t* motor, uint8_t x, uint8_t y);
void motor_toggle_speed(motor_t* motor);

#endif
