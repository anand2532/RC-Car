#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include "joystick.h"
#include "bluetooth.h"
#include "pins.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    joystick_t joystick;
    bluetooth_t bluetooth;
    uint8_t last_x;
    uint8_t last_y;
    uint8_t button_states[4];
    unsigned long last_activity_time;
} controller_t;

void controller_init(controller_t* ctrl);
void controller_setup(controller_t* ctrl);
void controller_update(controller_t* ctrl);

#ifdef __cplusplus
}
#endif

#endif
