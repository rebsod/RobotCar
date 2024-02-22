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



#define THRESHOLD_LEFT 550
#define THRESHOLD_CENTER 500
#define THRESHOLD_RIGHT 450
#define THRESHOLD_MR 605
#define THRESHOLD_ML 527

// loop cheker 
int count = 0;
bool CenterWhite = false;
bool CenterBlack = false;

// Function prototypes
void getSensorsValues(uint16_t* sensorValues, uint16_t* HIGHsensorValues, uint16_t* LOWsensorValues);
void getbluetoothCommand();
void trackfollowing(uint16_t* sensorValues);
void printSensorValue(uint16_t* sensorValues);
void printSensorValueHighLow(uint16_t* HIGHsensorValues, uint16_t* LOWsensorValues);
void loopcount(uint16_t* sensorValues, int numofcount);
// int ultrasonic();




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


  // MotorSpeed(100, 100);
  while (1) {

    getbluetoothCommand(); // Check for received commands
    loopcount(sensorValues, 2); // loop count sensor values and number of loops to stop the robot
    getSensorsValues(sensorValues, HIGHsensorValues, LOWsensorValues); // Read sensor values


  }
}
// get sensor values as return values let the function receive the address of the array
void getSensorsValues(uint16_t* sensorValues, uint16_t* HIGHsensorValues, uint16_t* LOWsensorValues) {
  sensorValues[0] = read_adc(sensor_l); // Read the ADC value for left sensor
  sensorValues[1] = read_adc(sensor_c); // Read the ADC value for center sensor
  sensorValues[2] = read_adc(sensor_r); // Read the ADC value for right sensor
  sensorValues[3] = read_adc(sensor_MR); // Read the ADC value for right sensor
  sensorValues[4] = read_adc(sensor_LR); // Read the ADC value for right sensor


  for (int i = 0; i < 5; i++) {
    //cheek if read value is higher than the high value
    if (sensorValues[i] > HIGHsensorValues[i]) {
      HIGHsensorValues[i] = sensorValues[i];
    }
    //cheek if read value is lower than the low value
    if (sensorValues[i] < LOWsensorValues[i]) {
      LOWsensorValues[i] = sensorValues[i];
    }

  }
  // delay for 1 second
  _delay_ms(50);
}

void getbluetoothCommand() {
  // Check the received command and act accordingly
  if (receivedCommand == START) {
    count = 0;
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

void trackfollowing(uint16_t* sensorValues) {
  int leftSpeed = 90;
  int rightSpeed = 90;
  int stopMootor = 0;


  // Assuming sensorValues[0] is left, sensorValues[1] is center, sensorValues[2] is right sensorValues[3]
  // is MR and sensorValues[4] LR

  if (sensorValues[2] > THRESHOLD_RIGHT) {
    leftSpeed = stopMootor;
  }
  else {
    leftSpeed = leftSpeed;
  }


  if (sensorValues[0] < THRESHOLD_RIGHT) {
    rightSpeed = stopMootor;
  }
  else {
    rightSpeed = rightSpeed;
  }

  MotorSpeed(leftSpeed, rightSpeed); // Set the motor speeds
}




void PrintSensorValue(uint16_t* sensorValues) {

  // Debugging the sensor values
  USART_SendString("\n\nLEFT: "); // Send the left string
  USART_Send16BitNumber(sensorValues[0]); // Send the left sensor value

  USART_SendString("\n CENTER: "); // Send the center string
  USART_Send16BitNumber(sensorValues[1]); // Send the center sensor value

  USART_SendString("\n RIGHT: "); // Send the right string
  USART_Send16BitNumber(sensorValues[2]); // Send the right sensor value

  USART_SendString("\n M_RIGHT: "); // Send the right string
  USART_Send16BitNumber(sensorValues[3]); // Send the right sensor value

  USART_SendString("\n L_RIGHT: "); // Send the right string
  USART_Send16BitNumber(sensorValues[4]); // Send the right sensor value
}

void PrintSensorValueHighLow(uint16_t* HIGHsensorValues, uint16_t* LOWsensorValues) {

  // print the high and low values
  USART_SendString("\n\nHIGH LEFT: "); // Send the left string
  USART_Send16BitNumber(HIGHsensorValues[0]); // Send the left sensor value
  USART_SendString("\nLOW LEFT: "); // Send the right string
  USART_Send16BitNumber(LOWsensorValues[0]); // Send the right sensor value

  USART_SendString("\nHIGH CENTER: "); // Send the center string
  USART_Send16BitNumber(HIGHsensorValues[1]); // Send the center sensor value
  USART_SendString("\nLOW CENTER: "); // Send the right string
  USART_Send16BitNumber(LOWsensorValues[1]); // Send the right sensor value

  USART_SendString("\nHIGH RIGHT: "); // Send the center string
  USART_Send16BitNumber(HIGHsensorValues[2]); // Send the center sensor value
  USART_SendString("\nLOW RIGHT: "); // Send the right string
  USART_Send16BitNumber(LOWsensorValues[2]); // Send the right sensor value

  USART_SendString("\nHIGH M_RIGHT: "); // Send the middel  string 
  USART_Send16BitNumber(HIGHsensorValues[3]); // Send the center sensor value
  USART_SendString("\nLOW M_RIGHT: "); // Send the right string
  USART_Send16BitNumber(LOWsensorValues[3]); // Send the right sensor value

  USART_SendString("\n\nHIGH M_LEFT: "); // Send the M_left string
  USART_Send16BitNumber(HIGHsensorValues[4]); // Send the M_left sensor value
  USART_SendString("\nLOW M_LEFT: "); // Send the M_right string
  USART_Send16BitNumber(LOWsensorValues[4]); // Send the right sensor value
}

void loopcount(uint16_t* sensorValues, int numofcount) {
  // loop count
  if (sensorValues[1] > 780) {
    CenterWhite = true;
    // USART_Send16BitNumber(sensorValues[1]);
  }
  if (sensorValues[1] < 240) {
    CenterBlack = true;
    // USART_Send16BitNumber(sensorValues[1]);
  }

  if (CenterWhite && CenterBlack) {
    count++;
    CenterWhite = false;
    CenterBlack = false;
    // USART_Send16BitNumber(count);
  }

  numofcount = numofcount * 2;
  if (count >= numofcount) { // use duble the loob count to stop the robot
    MotorSpeed(0, 0);
  }
}

// int ultrasonic(){
//     // debug the ultrasonic sensor
//     // trigger_pulse();  // Trigger the ultrasonic pulse
//     // _delay_ms(500);  // Wait for the echo to return

//     // float distance = calculate_distance();  // Calculate the distance
//     // USART_SendString("\n\nDistance: ");  // Send the distance message
//     // USART_Send16BitNumber((uint16_t)distance);  // Send the distance value
//     return 0
//     // _delay_ms(1000);  // Wait before the next measurement
// }