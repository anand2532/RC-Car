
#ifndef ARDUINO_H
#define ARDUINO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Arduino constants
#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2

// Pin definitions
#define LEFT_MOTOR_PIN1 11
#define LEFT_MOTOR_PIN2 12
#define RIGHT_MOTOR_PIN1 9
#define RIGHT_MOTOR_PIN2 10
#define LEFT_ENABLE_PIN 5
#define RIGHT_ENABLE_PIN 6

// Function declarations
void digitalWrite(uint8_t pin, uint8_t val);
void analogWrite(uint8_t pin, int val);
void pinMode(uint8_t pin, uint8_t mode);
unsigned long millis(void);
void delay(unsigned long ms);

#ifdef __cplusplus
}
#endif

#endif