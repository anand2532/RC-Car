#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

// HC 05 Pins
#define BT_RX_PIN 0               // Connects to HC-05 TX
#define BT_TX_PIN 1               // Connects to HC-05 RX
#define BT_STATE_PIN 8            // Connects to State
#define BT_EN_PIN 9               // Connects to Enable Pin

// Buttons
#define BUTTON_A_PIN 2
#define BUTTON_B_PIN 3
#define BUTTON_X_PIN 4

// Joystick
#define JOYSTICK_X_PIN A0
#define JOYSTICK_Y_PIN A1
#define JOYSTICK_BTN_PIN 5

// LED
#define LED_STATUS LED_BUILTIN

#endif