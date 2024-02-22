// HIGH LEFT: 742
// LOW LEFT: 312

//527


// HIGH CENTER: 651
// LOW CENTER: 131
//391

// HIGH RIGHT: 614
// LOW RIGHT: 62
//338

// HIGH M_RIGHT: 792
// LOW M_RIGHT: 417
//605
// HIGH L_RIGHT: 775
// LOW L_RIGHT: 280
//527 






//HIGH LEFT: 892
// LOW LEFT: 319
// HIGH CENTER: 892
// LOW CENTER: 140
// HIGH RIGHT: 896
// LOW RIGHT: 63
// HIGH M_RIGHT: 911
// LOW M_RIGHT: 428
// HIGH L_RIGHT: 915
// LOW L_RIGHT: 291




// HIGH LEFT: 926
// LOW LEFT: 300
// HIGH CENTER: 921
// LOW CENTER: 127
// HIGH RIGHT: 924
// LOW RIGHT: 51
// HIGH M_RIGHT: 927
// LOW M_RIGHT: 423
// HIGH L_RIGHT: 927
// LOW L_RIGHT: 287






// unused code

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