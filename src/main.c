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
#define sensor_MR ADC3D
#define sensor_LR ADC5D

// defund trush hold value for the sensors


// HIGH LEFT: 742
// LOW LEFT: 312
//527
#define THRESHOLD_LEFT 527
// HIGH CENTER: 651
// LOW CENTER: 131
//391
#define THRESHOLD_CENTER 391
// HIGH RIGHT: 614
// LOW RIGHT: 62
//338
#define THRESHOLD_RIGHT 338 
// HIGH M_RIGHT: 792
// LOW M_RIGHT: 417
//605
#define THRESHOLD_MR 605
// HIGH L_RIGHT: 775
// LOW L_RIGHT: 280
//527 
#define THRESHOLD_ML 527


// Function prototypes
// void getSensorsValues(uint16_t* sensorValues);
void getSensorsValues(uint16_t* sensorValues, uint16_t* HIGHsensorValues, uint16_t* LOWsensorValues);
// void getbluetoothCommand();
void followLine(uint16_t* sensorValues);




int main(void) {
  motors_init(); // Initialize motors
  USART_Init(); // Initialize USART for communication
  adc_init(); // Initialize ADC for sensor readings
  ultrasonic_init(); // Initialize ultrasonic sensor
  sei(); // Enable global interrupts
  // decler sensor values as array 
  uint16_t sensorValues[6];
  uint16_t HIGHsensorValues[6] = { 0,0,0,0,0,0 };
  uint16_t LOWsensorValues[6] = { 1023,1023,1023,1023,1023,1023 };






  // MotorSpeed(50, 50);
  while (1) {

    getbluetoothCommand(); // Check for received commands
    getSensorsValues(sensorValues, HIGHsensorValues, LOWsensorValues); // Read sensor values
    // followLine(sensorValues);// Follow the line based on sensor values
    // MotorSpeed(90, 0);
    // debug the ultrasonic sensor
    // trigger_pulse();  // Trigger the ultrasonic pulse
    // _delay_ms(500);  // Wait for the echo to return

    // float distance = calculate_distance();  // Calculate the distance
    // USART_SendString("\n\nDistance: ");  // Send the distance message
    // USART_Send16BitNumber((uint16_t)distance);  // Send the distance value

    // _delay_ms(1000);  // Wait before the next measurement

  }
}
// get sensor values as return values let the function receive the address of the array
void getSensorsValues(uint16_t* sensorValues, uint16_t* HIGHsensorValues, uint16_t* LOWsensorValues) {
  sensorValues[0] = read_adc(sensor_l); // Read the ADC value for left sensor
  sensorValues[1] = read_adc(sensor_c); // Read the ADC value for center sensor
  sensorValues[2] = read_adc(sensor_r); // Read the ADC value for right sensor
  sensorValues[3] = read_adc(sensor_MR); // Read the ADC value for right sensor
  sensorValues[4] = read_adc(sensor_LR); // Read the ADC value for right sensor


  //cheek if read value is higher than the high value
  if (sensorValues[0] > HIGHsensorValues[0]) {
    HIGHsensorValues[0] = sensorValues[0];
  }
  //cheek if read value is lower than the low value
  if (sensorValues[0] < LOWsensorValues[0]) {
    LOWsensorValues[0] = sensorValues[0];
  }
  //cheek if read value is higher than the high value
  if (sensorValues[1] > HIGHsensorValues[1]) {
    HIGHsensorValues[1] = sensorValues[1];
  }
  //cheek if read value is lower than the low value
  if (sensorValues[1] < LOWsensorValues[1]) {
    LOWsensorValues[1] = sensorValues[1];
  }
  //cheek if read value is higher than the high value
  if (sensorValues[2] > HIGHsensorValues[2]) {
    HIGHsensorValues[2] = sensorValues[2];
  }
  //cheek if read value is lower than the low value
  if (sensorValues[2] < LOWsensorValues[2]) {
    LOWsensorValues[2] = sensorValues[2];
  }
  //cheek if read value is higher than the high value
  if (sensorValues[3] > HIGHsensorValues[3]) {
    HIGHsensorValues[3] = sensorValues[3];
  }
  //cheek if read value is lower than the low value
  if (sensorValues[3] < LOWsensorValues[3]) {
    LOWsensorValues[3] = sensorValues[3];
  }
  //cheek if read value is higher than the high value
  if (sensorValues[4] > HIGHsensorValues[4]) {
    HIGHsensorValues[4] = sensorValues[4];
  }
  //cheek if read value is lower than the low value
  if (sensorValues[4] < LOWsensorValues[4]) {
    LOWsensorValues[4] = sensorValues[4];
  }



  // Debugging the sensor values

  // print the high and low values
  USART_SendString("\n\nHIGH LEFT: "); // Send the left string
  USART_Send16BitNumber(sensorValues[0]); // Send the left sensor value

  USART_SendString("\n CENTER: "); // Send the center string
  USART_Send16BitNumber(sensorValues[1]); // Send the center sensor value

  USART_SendString("\n RIGHT: "); // Send the right string
  USART_Send16BitNumber(sensorValues[2]); // Send the right sensor value

  USART_SendString("\n M_RIGHT: "); // Send the right string
  USART_Send16BitNumber(sensorValues[3]); // Send the right sensor value

  USART_SendString("\n L_RIGHT: "); // Send the right string
  USART_Send16BitNumber(sensorValues[4]); // Send the right sensor value

  // print the high and low values
  // USART_SendString("\n\nHIGH LEFT: "); // Send the left string
  // USART_Send16BitNumber(HIGHsensorValues[0]); // Send the left sensor value
  // USART_SendString("\nLOW LEFT: "); // Send the right string
  // USART_Send16BitNumber(LOWsensorValues[0]); // Send the right sensor value

  // USART_SendString("\nHIGH CENTER: "); // Send the center string
  // USART_Send16BitNumber(HIGHsensorValues[1]); // Send the center sensor value
  // USART_SendString("\nLOW CENTER: "); // Send the right string
  // USART_Send16BitNumber(LOWsensorValues[1]); // Send the right sensor value


  // USART_SendString("\nHIGH RIGHT: "); // Send the right string
  // USART_Send16BitNumber(HIGHsensorValues[2]); // Send the right sensor value
  // USART_SendString("\nLOW RIGHT: "); // Send the right string
  // USART_Send16BitNumber(LOWsensorValues[2]); // Send the right sensor value

  // USART_SendString("\nHIGH M_RIGHT: "); // Send the right string
  // USART_Send16BitNumber(HIGHsensorValues[3]); // Send the right sensor value
  // USART_SendString("\nLOW M_RIGHT: "); // Send the right string
  // USART_Send16BitNumber(LOWsensorValues[3]); // Send the right sensor value

  // USART_SendString("\nHIGH L_RIGHT: "); // Send the right string
  // USART_Send16BitNumber(HIGHsensorValues[4]); // Send the right sensor value
  // USART_SendString("\nLOW L_RIGHT: "); // Send the right string
  // USART_Send16BitNumber(LOWsensorValues[4]); // Send the right sensor value

  // delay for 1 second
  _delay_ms(100);
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
  // Assuming sensorValues[0] is left, sensorValues[1] is center, sensorValues[2] is right sensorValues[3]
  // is MR and sensorValues[4] LR


  if (sensorValues[2] > (THRESHOLD_RIGHT + 35)) {
    MotorSpeed(00, 80);
  }

  else if (sensorValues[3] > (THRESHOLD_MR + 35)) {
    MotorSpeed(0, 80);
  }


  else if (sensorValues[0] < (THRESHOLD_LEFT + 35)) {
    MotorSpeed(80, 0);
  }

  else if (sensorValues[4] < (THRESHOLD_ML + 35)) {
    MotorSpeed(80, 0);
  }
  else
  {
    MotorSpeed(80, 80);
  }




}


