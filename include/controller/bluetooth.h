#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "pins.h"
#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t connected;
    unsigned long last_send_time;
    unsigned long min_send_interval;
} bluetooth_t;

void bluetooth_init(bluetooth_t* bt);
void bluetooth_begin(bluetooth_t* bt, long baud_rate);
uint8_t bluetooth_is_connected(bluetooth_t* bt);
void bluetooth_send_joystick(bluetooth_t* bt, uint8_t x, uint8_t y);
void bluetooth_send_button(bluetooth_t* bt, char button);
uint8_t bluetooth_can_send(bluetooth_t* bt);

#ifdef __cplusplus
}
#endif

#endif


