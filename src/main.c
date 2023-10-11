#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "uart.h"
#include "dio.h"

#define PIN_BUTTON 4
#define PORT_BUTTON 'b'
#define PIN_LED 5
#define PORT_LED 'b'
#define STRBUFFER_LENGTH 8


//variables edited by interrupts
char strbuf[STRBUFFER_LENGTH];
volatile char received;
volatile int16_t i;

//constant strings to compare input to
const char* textOn = "led on";
#define ON_LENGTH 6
const char* textOff = "led off";
#define OFF_LENGTH 7


void setup();


int main()
{
  setup();

  while(1){
    //check for "string received" flag
    if(received == -1){
      //reset flag then compare to desired string
      received = 0;
      if(i == ON_LENGTH && strncmp(strbuf, textOn, ON_LENGTH) == 0) {
        //turn LED on 
        dio_SetPin(PORT_LED, PIN_LED, 1);
      }
      else if(i == OFF_LENGTH && strncmp(strbuf, textOff, OFF_LENGTH) == 0) {
        //turn LED off
        dio_SetPin(PORT_LED, PIN_LED, 0);
      }
      i = 0;
    }

  }

}

void setup()
{
  uart_Init(9600);

  dio_SetDirection(PORT_LED, PIN_LED, OUTPUT);
  dio_SetDirection(PORT_BUTTON, PIN_BUTTON, INPUT_PULLUP);

  cli(); //disable interrupts during setting up
  PCICR |= 1; //enable interrupts for port b
  PCMSK0 = (1 << PIN_BUTTON); //enable interrupt for button pin
  UCSR0B |= (1 << RXCIE0); //enable interrupt for rx
  sei(); //reenable interrupts
}

ISR(PCINT0_vect) //interrupt handler for button pin
{
    if(dio_GetPin('b', PIN_BUTTON) == 0) uart_SendString("button pressed\n", 15);
}

ISR(USART_RX_vect) //interrupt handler for rx 
{
  received = uart_Receive(); //received char from data register
  if(received == '\n' || received == '\0') //newline and end characters determine end of user input
  {
    received = -1;
    //set flag, indicating a full line of user input was received 
  } else strbuf[i++] = received;

  if(i >= STRBUFFER_LENGTH) i = 0; //reset i if it exceeds size of array
}
