#ifndef CAR_H
#define CAR_H

#include "common.h"
#include "motor.h"
#include "uart.h"

const uint8_t LED_PIN = 13;
const unsigned long POWER_DOWN_TIMEOUT = 60000;

typedef struct {
    uart_t uart;
    motor_t motor;
    char last_command[32];
    unsigned long last_activity_time;
} car_t;

void car_init(car_t* car);
void car_setup(car_t* car);
void car_loop(car_t* car);

#endif