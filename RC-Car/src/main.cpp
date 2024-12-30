#include<Arduino.h>


void sendATCommand(String command, String expectedResponse);

void setup() {
 
  Serial.begin(9600);
  while (!Serial); 
  Serial.println("Starting HC-05 Test...");

  
  Serial1.begin(9600);  
  delay(2000);  

  for (int i; i<=10; i++) {
        // Send basic AT command to check if module responds
    sendATCommand("AT", "OK");

    // Test the device name
    sendATCommand("AT+NAME", "HC-05");

    // Test baud rate
    sendATCommand("AT+BAUD?", "+BAUD=9600");

    // Change baud rate (Test with baud rate 9600)
    sendATCommand("AT+BAUD4", "OK");

    // Check the firmware version
    sendATCommand("AT+VERSION", "+VERSION=");

    // Check connection state (whether it is connected to a device)
    sendATCommand("AT+STATE?", "+STATE=");

    // Check the current module role (Master or Slave)
    sendATCommand("AT+ROLE?", "+ROLE=");

    // Change module role to Master
    sendATCommand("AT+ROLE=1", "OK");

    // Reset the module
    sendATCommand("AT+RESET", "OK");

    // Change the device name
    sendATCommand("AT+NAME=NewName", "OK");

    Serial.println("HC-05 Test Completed.");
  }


}

void loop() {
  // No need for continuous loop, since all tests are done in setup.
}

// Function to send AT command and check the expected response
void sendATCommand(String command, String expectedResponse) {
  Serial.print("Sending: ");
  Serial.println(command);
  Serial1.println(command);  // Send command to HC-05

  delay(1000);  // Wait for the HC-05 to respond

  String response = "";
  while (Serial1.available()) {
    response += char(Serial1.read());  // Read the response from HC-05
  }

  // Check if the response matches the expected one
  Serial.print("Response: ");
  Serial.println(response);
  if (response.indexOf(expectedResponse) != -1) {
    Serial.println("Test Passed");
  } else {
    Serial.println("Test Failed");
  }
  Serial.println();  // Add an empty line for readability
}
