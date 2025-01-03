#include "uart.h"

void uart_init(uart_t* uart) {
    uart->buffer_pos = 0;
}

void uart_begin(uart_t* uart, long baud) {
    Serial.begin(baud);
}

int uart_receive(uart_t* uart, char* command, size_t max_len) {
    while (Serial.available() > 0) {
        char c = Serial.read();
        if (uart->buffer_pos < sizeof(uart->buffer) - 1) {
            uart->buffer[uart->buffer_pos++] = c;
        }
        if (c == '#') {
            uart->buffer[uart->buffer_pos] = '\0';
            int len = uart->buffer_pos;
            strncpy(command, uart->buffer, max_len - 1);
            command[max_len - 1] = '\0';
            uart->buffer_pos = 0;
            return len;
        }
    }
    return 0;
}

void uart_send(uart_t* uart, const char* message) {
    Serial.println(message);
}
