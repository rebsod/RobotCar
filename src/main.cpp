#include <avr/io.h>
#include <stdbool.h> // Include to support 'bool' type
#include <avr/interrupt.h> // Include for ISR
#include "Motor_C.h" // Assumed to contain the motors_init() and MotorSpeed() function declarations
#include "RxTx.h" // Assumed to contain the USART_Init() function declaration and receivedCommand variable
#include <util/delay.h> // Include for _delay_ms()

// Define the commands to be received from the base station
#define START 'A'
#define STOP_AND_GO 'B'
#define STOP 'C'

int main(void) {
  motors_init(); // Initialize motors
  USART_Init(); // Initialize USART for communication
  sei(); // Enable global interrupts

  while (1) {
    // Check the received command and act accordingly
    if (receivedCommand == START) {
      MotorSpeed(100, 100); // Set motors to full speed
      receivedCommand = 0; // Reset command to avoid repeated execution
    }
    else if (receivedCommand == STOP_AND_GO) {
      MotorSpeed(0, 0); // Stop motors due to penalty
      _delay_ms(5000); // Wait for 5 seconds
      receivedCommand = 0; // Reset command
      MotorSpeed(100, 100); // Set motors to full speed
    }
    else if (receivedCommand == STOP) {
      MotorSpeed(0, 0); // Stop motors
      receivedCommand = 0; // Reset command
    }

  }
}
