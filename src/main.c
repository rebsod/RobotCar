#include <avr/io.h>
#include <stdbool.h> // Include to support 'bool' type
#include <avr/interrupt.h> // Include for ISR
#include "Motor_C.h" // Assumed to contain the motors_init() and MotorSpeed() function declarations
#include "RxTx.h" // Assumed to contain the USART_Init() function declaration and receivedCommand variable
#include <util/delay.h> // Include for _delay_ms()
#include "ADC.h" // Assumed to contain the ADC_Init() and ADC_Read() function declarations
#include "ultrasonic.h" // Assumed to contain the ultrasonic_init() and ultrasonic_read() function declarations



// Define the commands to be received from the base station
#define START 'A'
#define STOP_AND_GO 'B'
#define STOP 'C'

//sensor pins

#define sensor_l ADC2D 
#define sensor_c ADC0D
#define sensor_r ADC1D

// defund trush hold value for the sensors

#define THRESHOLD_LOW 600
#define THRESHOLD_HIGH 700


// Function prototypes
void getSensorsValues(uint16_t* sensorValues);
void getbluetoothCommand();
void followLine(uint16_t* sensorValues);




int main(void) {
  motors_init(); // Initialize motors
  USART_Init(); // Initialize USART for communication
  adc_init(); // Initialize ADC for sensor readings
  ultrasonic_init(); // Initialize ultrasonic sensor
  sei(); // Enable global interrupts
  // decler sensor values as array 
  uint16_t sensorValues[3];
  MotorSpeed(0, 0);
  while (1) {

    getbluetoothCommand(); // Check for received commands
    getSensorsValues(sensorValues); // Read sensor values
    // followLine(sensorValues);// Follow the line based on sensor values

    // debug the ultrasonic sensor
    trigger_pulse();  // Trigger the ultrasonic pulse
    _delay_ms(1000);  // Wait for the echo to return

    float distance = calculate_distance();  // Calculate the distance
    USART_SendString("\n\nDistance: ");  // Send the distance message
    USART_Send16BitNumber((uint16_t)distance);  // Send the distance value

    _delay_ms(1000);  // Wait before the next measurement

  }
}
// get sensor values as return values let the function receive the address of the array
void getSensorsValues(uint16_t* sensorValues) {
  sensorValues[0] = read_adc(sensor_l); // Read the ADC value for left sensor
  sensorValues[1] = read_adc(sensor_c); // Read the ADC value for center sensor
  sensorValues[2] = read_adc(sensor_r); // Read the ADC value for right sensor

  // Debugging the sensor values
  USART_SendString("\n\nLEFT: "); // Send the left string
  USART_Send16BitNumber(sensorValues[0]); // Send the left sensor value
  USART_SendString("\nCENTER: "); // Send the center string
  USART_Send16BitNumber(sensorValues[1]); // Send the center sensor value
  USART_SendString("\nRIGHT: "); // Send the right string
  USART_Send16BitNumber(sensorValues[2]); // Send the right sensor value

  // delay for 1 second
  _delay_ms(1000);
}

void getbluetoothCommand() {
  // Check the received command and act accordingly
  if (receivedCommand == START) {
    MotorSpeed(50, 50); // Set motors to full speed
    receivedCommand = 0; // Reset command to avoid repeated execution
  }
  else if (receivedCommand == STOP_AND_GO) {
    MotorSpeed(0, 0); // Stop motors due to penalty
    _delay_ms(5000); // Wait for 5 seconds
    receivedCommand = 0; // Reset command
    MotorSpeed(50, 50); // Set motors to full speed
  }
  else if (receivedCommand == STOP) {
    MotorSpeed(0, 0); // Stop motors
    receivedCommand = 0; // Reset command
    // wait antil the command is changed
    while (receivedCommand != START) {
    }

  }
}

void followLine(uint16_t* sensorValues) {
  // Assuming sensorValues[0] is left, sensorValues[1] is center, sensorValues[2] is right
  if (sensorValues[0] > THRESHOLD_HIGH && sensorValues[1] > THRESHOLD_HIGH && sensorValues[2] > THRESHOLD_HIGH) {
    MotorSpeed(50, 50); // Move forward
  }
  else if (sensorValues[0] > THRESHOLD_HIGH && sensorValues[1] < THRESHOLD_LOW && sensorValues[2] > THRESHOLD_HIGH) {
    MotorSpeed(50, 0); // Turn right
  }
  else if (sensorValues[0] < THRESHOLD_LOW && sensorValues[1] > THRESHOLD_HIGH && sensorValues[2] > THRESHOLD_HIGH) {
    MotorSpeed(0, 50); // Turn left
  }
  else if (sensorValues[0] < THRESHOLD_LOW && sensorValues[1] < THRESHOLD_LOW && sensorValues[2] > THRESHOLD_HIGH) {
    MotorSpeed(0, 50); // Turn left
  }
  else if (sensorValues[0] > THRESHOLD_HIGH && sensorValues[1] < THRESHOLD_LOW && sensorValues[2] < THRESHOLD_LOW) {
    MotorSpeed(50, 0); // Turn right
  }
  else if (sensorValues[0] < THRESHOLD_LOW && sensorValues[1] < THRESHOLD_LOW && sensorValues[2] > THRESHOLD_HIGH) {
    MotorSpeed(0, 50); // Turn left
  }
  else if (sensorValues[0] < THRESHOLD_LOW && sensorValues[1] > THRESHOLD_HIGH && sensorValues[2] < THRESHOLD_LOW) {
    MotorSpeed(0, 50); // Turn left
  }
  else if (sensorValues[0] < THRESHOLD_LOW && sensorValues[1] < THRESHOLD_LOW && sensorValues[2] < THRESHOLD_LOW) {
    MotorSpeed(50, 0); // Turn right
  }
  else {
    MotorSpeed(50, 50); // Move forward
  }
}
