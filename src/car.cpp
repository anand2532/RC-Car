#include "car.h"
#include <avr/sleep.h>
#include <stdio.h>

void car_init(car_t* car) {
    uart_init(&car->uart);
    motor_init(&car->motor);
    car->last_activity_time = millis();
}

void car_setup(car_t* car) {
    pinMode(LED_PIN, OUTPUT);
    uart_begin(&car->uart, 9600);
    motor_setup(&car->motor);
}

void car_loop(car_t* car) {
    delay(50);
    
    char command[32];
    if (uart_receive(&car->uart, command, sizeof(command)) > 2) {
        if (command[0] == 'J') {
            int x = 0, y = 0;
            sscanf(command, "J%d,%d#", &x, &y);
            motor_drive(&car->motor, (uint8_t)x, (uint8_t)y);
        } else if (command[0] == 'B') {
            switch(command[1]) {
                case 'L':
                    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
                    break;
                case 'S':
                    motor_toggle_speed(&car->motor);
                    break;
            }
        }
        car->last_activity_time = millis();
    }
    
    if (millis() - car->last_activity_time >= POWER_DOWN_TIMEOUT) {
        digitalWrite(LED_PIN, LOW);
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();
        sleep_mode();
        sleep_disable();
        car->last_activity_time = millis();
    }
}
