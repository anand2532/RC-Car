#include <Arduino.h>
#include "controller.h"

static controller_t controller;

void setup() {
  Serial.begin(9600);    //Debug serial
  while (!Serial) {
    ;                    // wait for Serial port to connect                    
  }
  controller_init(&controller);
  controller_setup(&controller);
}

void loop() {
  controller_update(&controller);
}