#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Define pins for trigger and echo
#define TRIGGER_DDR DDRB
#define TRIGGER_PORT PORTB
#define TRIGGER_PIN 4  // Pin 13 on AVR, PB5
#define ECHO_DDR DDRB
#define ECHO_PIN 5     // Pin 12 on AVR, PB4

// Timer settings - using 1024 prescaler
#define TIMER_PRESCALER 1024UL
#define CLOCK_FREQUENCY 16000000UL  // 16 MHz

volatile uint16_t pulse_width = 0;

void ultrasonic_init() {
    // Set trigger pin as output
    TRIGGER_DDR |= (1 << TRIGGER_PIN);

    // Set echo pin as input
    ECHO_DDR &= ~(1 << ECHO_PIN);

    // Enable pin change interrupt on echo pin
    PCICR |= (1 << PCIE0);
    PCMSK0 |= (1 << ECHO_PIN);

    // Enable global interrupts
    sei();

    // Configure Timer1
    TCCR1B |= (1 << CS10) | (1 << CS12);  // Prescaler 1024
}

void trigger_pulse() {
    // Generate trigger pulse
    TRIGGER_PORT |= (1 << TRIGGER_PIN);
    _delay_us(10);
    TRIGGER_PORT &= ~(1 << TRIGGER_PIN);
}

ISR(PCINT0_vect) {
    static uint16_t rising_edge_time = 0;

    // Check if echo pin is high
    if (PINB & (1 << ECHO_PIN)) {
        rising_edge_time = TCNT1;  // Capture time at rising edge
    }
    else {
        uint16_t falling_edge_time = TCNT1;  // Capture time at falling edge
        pulse_width = falling_edge_time - rising_edge_time;
    }
}

// Function to calculate distance in cm
float calculate_distance() {
    // Time in seconds = number of ticks * prescaler / clock frequency
    float time_seconds = pulse_width * (float)TIMER_PRESCALER / CLOCK_FREQUENCY;

    // Distance = speed of sound in cm/s * time / 2
    // Speed of sound = 34300 cm/s at room temperature
    float distance_cm = (time_seconds * 34300) / 2;
    // conver to int
    return distance_cm;
}







