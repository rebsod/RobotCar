#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 16000000UL // Set CPU frequency to 16 MHz
#endif

#define BAUD 9600
#define MYUBRR ((F_CPU / 16 / BAUD) - 1)

volatile uint8_t receivedCommand;

void USART_Init(void) {
    UBRR0H = (uint8_t)(MYUBRR >> 8);
    UBRR0L = (uint8_t)MYUBRR;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void USART_SendChar(uint8_t data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void USART_SendString(const char* data) {
    while (*data) {
        USART_SendChar(*data++);
    }
}

void USART_Send8BitNumber(uint8_t number) {
    char buffer[4]; // Enough for 0-255 plus null terminator
    uint8_t i = 3; // Start from the end of the buffer
    buffer[i--] = '\0'; // Null-terminate the string

    do {
        buffer[i--] = (number % 10) + '0'; // Convert digit to char and store
        number /= 10; // Move to the next digit
    } while (number && i);

    USART_SendString(&buffer[i + 1]); // Send the number string
}

void USART_Send16BitNumber(uint16_t number) {
    char buffer[6]; // Enough for 0-65535 plus null terminator
    uint8_t i = 5; // Start from the end of the buffer
    buffer[i--] = '\0'; // Null-terminate the string

    do {
        buffer[i--] = (number % 10) + '0'; // Convert digit to char and store
        number /= 10; // Move to the next digit
    } while (number && i);

    USART_SendString(&buffer[i + 1]); // Send the number string
}

uint8_t USART_Receive(void) {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

ISR(USART_RX_vect) {
    receivedCommand = UDR0;
}

