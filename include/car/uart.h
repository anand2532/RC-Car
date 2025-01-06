#ifndef UART_H
#define UART_H

#include "common.h"

typedef struct {
    char buffer[32];
    uint8_t buffer_pos;
} uart_t;

void uart_init(uart_t* uart);
void uart_begin(uart_t* uart, long baud);
int uart_receive(uart_t* uart, char* command, size_t max_len);
void uart_send(uart_t* uart, const char* message);

#endif