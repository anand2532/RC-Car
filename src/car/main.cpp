#include <Arduino.h>
#include "car.h"

car_t car;

void setup() {
    car_init(&car);
    car_setup(&car);
}

void loop() {
    car_loop(&car);
}