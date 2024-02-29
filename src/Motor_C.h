#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000UL // Set CPU frequency to 16 MHz
#endif

// Motor control pins and PWM parameters
#define LEFT_MOTOR_PIN 5
#define RIGHT_MOTOR_PIN 6
#define MOTOR_PWM_TIMER_TOP 255
#define MOTOR_MINIMUM_SPEED 0
#define MOTOR_MAXIMUM_SPEED 100

// Motor control setup
#define MOTORS_DDRx DDRD
#define LEFT_MOTOR_OCnx OCR0B
#define RIGHT_MOTOR_OCnx OCR0A

#define PRESCALER 8 // Timer prescaler value

// Initialize and start the PWM timer
void initializePWM(void) {
    TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00)); // Clear previous settings // with timer 0
    if (PRESCALER == 8) TCCR0B |= (1 << CS01);
    else if (PRESCALER == 64) TCCR0B |= (1 << CS01) | (1 << CS00);
    else if (PRESCALER == 256) TCCR0B |= (1 << CS02);
    else if (PRESCALER == 1024) TCCR0B |= (1 << CS02) | (1 << CS00);
}

// Adjust motor speeds with safety checks
void MotorSpeed(int leftSpeed, int rightSpeed) {
    // Check if the speed is within the allowed range
    if (leftSpeed >= MOTOR_MINIMUM_SPEED && leftSpeed <= MOTOR_MAXIMUM_SPEED)
        // Set the PWM duty cycle for the left motor
        LEFT_MOTOR_OCnx = (leftSpeed * MOTOR_PWM_TIMER_TOP) / 100;
    if (rightSpeed >= MOTOR_MINIMUM_SPEED && rightSpeed <= MOTOR_MAXIMUM_SPEED)
        RIGHT_MOTOR_OCnx = (rightSpeed * MOTOR_PWM_TIMER_TOP) / 100;
}

// Setup motor control pins for output and configure PWM
void motors_init(void) {
    MOTORS_DDRx |= (1 << LEFT_MOTOR_PIN) | (1 << RIGHT_MOTOR_PIN); // Configure motor pins as output
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) | (1 << WGM01); // Set PWM mode 
    initializePWM(); // Activate the PWM timer
}

