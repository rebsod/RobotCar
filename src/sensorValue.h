#include "ADC.h" // Assumed to contain the ADC_Init() and ADC_Read() function declarations
#include "RxTx.h" // Assumed to contain the USART_Init() function declaration and receivedCommand variable
#include <util/delay.h> // Include for _delay_ms()



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
    // USART_SendString("\n\nHIGH LEFT: "); // Send the left string
    // USART_Send16BitNumber(sensorValues[0]); // Send the left sensor value

    // USART_SendString("\n CENTER: "); // Send the center string
    // USART_Send16BitNumber(sensorValues[1]); // Send the center sensor value

    // USART_SendString("\n RIGHT: "); // Send the right string
    // USART_Send16BitNumber(sensorValues[2]); // Send the right sensor value

    // USART_SendString("\n M_RIGHT: "); // Send the right string
    // USART_Send16BitNumber(sensorValues[3]); // Send the right sensor value

    // USART_SendString("\n L_RIGHT: "); // Send the right string
    // USART_Send16BitNumber(sensorValues[4]); // Send the right sensor value

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
    _delay_ms(50);
}
