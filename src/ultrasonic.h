#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define TRIGGER_DDR DDRB
#define TRIGGER_PORT PORTB
#define TRIGGER_PIN 4
#define TRIGGER_FREQUENCY 10 // Manual trigger delay between Trigger HIGH and LOW.

#define ECHO_DDR DDRB
#define ECHO_PORT PORTB
#define ECHO_PIN 5
#define ECHO_PCINT PCINT5
#define ECHO_PCICR_BIT PCIE0
#define ECHO_PCMSK PCMSK0
#define ECHO_PCINT_vect PCINT0_vect

#define TIMER2_PRESCALER_BITS ((1 << CS22) | (1 << CS21) | (1 << CS20)) // 1024 prescaler
#define TIMER2_OVERFLOW 10

volatile uint16_t pulse_width = 0; // Stores the time taken to reach the receiver.
volatile uint8_t i = 0;

void ultrasonic_init() {
    // Set Trigger pin as OUTPUT, and ECHO pin as INPUT.
    TRIGGER_DDR |= (1 << TRIGGER_PIN);
    ECHO_DDR &= ~(1 << ECHO_PIN);

    // Enable pin change interrupt for the echo pin.
    PCICR |= (1 << ECHO_PCICR_BIT);
    ECHO_PCMSK |= (1 << ECHO_PCINT);

    // Enable global interrupts.
    sei();

    // Configure Timer2 for CTC mode with OCR2A as the top value.
    OCR2A = 255;
    TIMSK2 |= (1 << OCIE2A); // Enable CTC interrupt
    TCCR2A |= (1 << WGM21);  // CTC mode
    TCCR2B |= TIMER2_PRESCALER_BITS; // Set prescaler
}

void trigger() {
    TRIGGER_PORT |= (1 << TRIGGER_PIN);
    _delay_ms(TRIGGER_FREQUENCY);
    TRIGGER_PORT &= ~(1 << TRIGGER_PIN);
}

ISR(ECHO_PCINT_vect) {
    if (!(ECHO_PORT & (1 << ECHO_PIN))) { // ECHO pin goes LOW
        pulse_width = TCNT2; // Read Timer2 value
        // Additional conditions or actions can be added here
    }
    TCNT2 = 0; // Reset Timer2
}
// Timer2 CTC interrupt handler to trigger the ultrasonic sensor.
ISR(TIMER2_COMPA_vect) {
    i = (i >= TIMER2_OVERFLOW) ? 0 : i + 1;
    if (i == 0) {
        TRIGGER_PORT |= (1 << TRIGGER_PIN); // Set Trigger HIGH
    }
    else if (i == TIMER2_OVERFLOW) {
        TRIGGER_PORT &= ~(1 << TRIGGER_PIN); // Set Trigger LOW
    }
}
