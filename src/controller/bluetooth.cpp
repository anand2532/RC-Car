#include "bluetooth.h"

void bluetooth_init(bluetooth_t* bt) {
    bt->connected = 0;
    bt->last_send_time = 0;
    bt->min_send_interval = 20;           // 20ms between sends
}

void bluetooth_begin(bluetooth_t* bt, long baud_rate) {
    Serial1.begin(baud_rate);
    pinMode(BT_STATE_PIN, INPUT);
}

uint8_t bluetooth_is_connected(bluetooth_t* bt) {
    bt->connected = digitalRead(BT_STATE_PIN) == HIGH;
    return bt->connected;
}

void bluetooth_send_joystick(bluetooth_t* bt, uint8_t x, uint8_t y) {
    if (!bluetooth_can_send(bt) || !bt->connected) return;

    char buffer[16];
    snprintf(buffer, sizeof(buffer), "J%d,%d#", x, y);
    Serial1.print(buffer);
    bt->last_send_time = millis();
}

void bluetooth_send_button(bluetooth_t* bt, char button) {
    if (!bluetooth_can_send(bt) || !bt->connected) return;

    char buffer[4];
    snprintf(buffer, sizeof(buffer), "B%c#", button);
    Serial1.print(buffer);
    bt->last_send_time = millis();
}

uint8_t bluetooth_can_send(bluetooth_t* bt) {
return (millis() - bt->last_send_time) >= bt->min_send_interval;
}

