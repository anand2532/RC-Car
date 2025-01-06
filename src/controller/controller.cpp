#include "controller.h"
#include <string>


static void process_buttons(controller_t* ctrl);
static void process_joystick(controller_t* ctrl);

void controller_init(controller_t* ctrl) {
    joystick_init(&ctrl->joystick);
    bluetooth_init(&ctrl->bluetooth);
    ctrl->last_x = 128;
    ctrl->last_y = 128;
    memset(ctrl->button_states, 0, sizeof(ctrl->button_states));
    ctrl->last_activity_time = 0;
}

void controller_setup(controller_t* ctrl) {
    // Init Pins
    pinMode(LED_STATUS, OUTPUT);
    pinMode(BUTTON_A_PIN, INPUT_PULLUP);
    pinMode(BUTTON_B_PIN, INPUT_PULLUP);
    pinMode(BUTTON_X_PIN, INPUT_PULLUP);

    // Init Components
    joystick_setup(&ctrl->joystick);
    bluetooth_begin(&ctrl->bluetooth, 9600);

    // Calibrate joystick 
    digitalWrite(LED_STATUS, HIGH);
    delay(1000);  // Wait for joystick to stabalize
    joystick_calibrate(&ctrl->joystick);
    digitalWrite(LED_STATUS, LOW);
}

static void process_buttons(controller_t* ctrl) {
    uint8_t current_state[4] = {
        !digitalRead(BUTTON_A_PIN),
        !digitalRead(BUTTON_B_PIN),
        !digitalRead(BUTTON_X_PIN),
        joystick_read_button(&ctrl->joystick)
    };

    const char buttons[4] = {'A', 'B', 'X', 'J'};
    uint8_t any_button_pressed = 0;

    for(int i = 0; i < 4; i++) {
        if(current_state[i] && !ctrl->button_states[i]) {
            bluetooth_send_button(&ctrl->bluetooth, buttons[i]);
            ctrl->last_activity_time = millis();
        }
        ctrl->button_states[i] = current_state[i];
        any_button_pressed |= current_state[i];
    }

    digitalWrite(LED_STATUS, any_button_pressed ? HIGH : LOW);
}

static void process_joystick(controller_t* ctrl) {
    uint8_t x = joystick_read_x(&ctrl->joystick);
    uint8_t y = joystick_read_y(&ctrl->joystick);

    if(abs(x - ctrl->last_x) > 3 || abs(y - ctrl->last_y) > 3) {
        bluetooth_send_joystick(&ctrl->bluetooth, x, y);
        ctrl->last_x = x;
        ctrl->last_y = y;
        ctrl->last_activity_time = millis();
    }
}

void controller_update(controller_t* ctrl) {
    if(bluetooth_is_connected(&ctrl->bluetooth)) {
        process_buttons(ctrl);
        process_joystick(ctrl);
    } else {
        // Blink LED when not connected 
        digitalWrite(LED_STATUS, (millis() / 500) % 2);
    }

     delay(10);        // Small delay for stability
}

