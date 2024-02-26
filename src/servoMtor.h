#include <avr/io.h>
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU 16000000UL // Clock Speed
#endif

// Servo control on pin 9
#define SERVO_DDR DDRB
#define SERVO_PIN PB1  // Pin 9 is PB1 on ATmega328P (Arduino Uno)
#define SERVO_OCnx OCR1A  // Use OCR1A for PWM

#define TOP 20000
#define SERVO_MIN 950
#define SERVO_MAX 4700
#define RANGE (SERVO_MAX - SERVO_MIN) / 180

void servo_init(void) {
    SERVO_DDR |= (1 << SERVO_PIN);  // Set pin 9 as OUTPUT

    // Timer 1 - Fast PWM mode with ICR1 as TOP, non-inverting mode
    TCCR1A = (1 << WGM11) | (1 << COM1A1);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);  // Prescaler = 8

    ICR1 = TOP;  // Set TOP value for a 50Hz PWM signal
}

void set_angle(int angle) {
    SERVO_OCnx = SERVO_MIN + ((long)RANGE * angle);
}
