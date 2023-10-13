#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "dio.h" 
#include "main.h"

ISR(PORTB_INTERRUPT) //interrupt handler for button pin
{
    if(dio_GetPin('b', PIN_BUTTON) == 0) uart_SendString("button pressed\n", 15);
}

ISR(UART_RX_INTERRUPT) //interrupt handler for rx 
{
  received = uart_Receive(); //received char from data register
  if(received == '\n' || received == '\0') //newline and end characters determine end of user input
  {
    received = -1;
    //set flag, indicating a full line of user input was received 
  } else strbuf[i++] = received;

  if(i >= STRBUFFER_LENGTH) i = 0; //reset i if it exceeds size of array
}
