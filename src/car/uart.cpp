// #include "uart.h"

// void uart_init(uart_t* uart) {
//     uart->buffer_pos = 0;
// }

// void uart_begin(uart_t* uart, long baud) {
//     Serial.begin(baud);
// }

// int uart_receive(uart_t* uart, char* command, size_t max_len) {
//     while (Serial.available() > 0) {
//         char c = Serial.read();
//         Serial.println(c);
//         if (uart->buffer_pos < sizeof(uart->buffer) - 1) {
//             uart->buffer[uart->buffer_pos++] = c;
//         }
//         if (c == '#') {
//             uart->buffer[uart->buffer_pos] = '\0';
//             int len = uart->buffer_pos;
//             strncpy(command, uart->buffer, max_len - 1);
//             command[max_len - 1] = '\0';
//             uart->buffer_pos = 0;
//             return len;
//         }
//     }
//     return 0;
// }

// void uart_send(uart_t* uart, const char* message) {
//     Serial.println(message);
// }


#include "uart.h"
#include <SoftwareSerial.h>

// Define the HC-05 connection pins
#define BT_RX 2    // Connect to HC-05 TX
#define BT_TX 3    // Connect to HC-05 RX

// Create a SoftwareSerial object for the HC-05
SoftwareSerial BTSerial(BT_RX, BT_TX);

void uart_init(uart_t* uart) {
    uart->buffer_pos = 0;
    // Initialize both hardware Serial (for debugging) and BT Serial
    Serial.begin(9600);     // For debugging output
    BTSerial.begin(9600);   // Must match HC-05 baud rate
}

void uart_begin(uart_t* uart, long baud) {
    // This function is kept for compatibility but uses BTSerial
    BTSerial.begin(baud);
}

int uart_receive(uart_t* uart, char* command, size_t max_len) {
    // Check if data is available from Bluetooth
    while (BTSerial.available() > 0) {
        char c = BTSerial.read();
        
        // Echo received character to Serial for debugging
        Serial.print("Received: ");
        Serial.println(c);
        
        // Store character in buffer if there's space
        if (uart->buffer_pos < sizeof(uart->buffer) - 1) {
            uart->buffer[uart->buffer_pos++] = c;
            
            // Check for message terminator '#'
            if (c == '#') {
                // Null terminate the string
                uart->buffer[uart->buffer_pos] = '\0';
                
                // Copy to output buffer with safety checks
                int len = uart->buffer_pos;
                strncpy(command, uart->buffer, max_len - 1);
                command[max_len - 1] = '\0';
                
                // Reset buffer position for next message
                uart->buffer_pos = 0;
                
                // Return length of received message
                return len;
            }
        } else {
            // Buffer overflow protection
            uart->buffer_pos = 0;  // Reset buffer
            Serial.println("Buffer overflow - message discarded");
        }
    }
    return 0;  // No complete message received yet
}

void uart_send(uart_t* uart, const char* message) {
    // Send message through Bluetooth
    BTSerial.println(message);
    
    // Echo to Serial for debugging
    Serial.print("Sent: ");
    Serial.println(message);
}