#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "uart.h"

#define PIN_BUTTON 4
#define PIN_LED 5
#define STRBUFFER_LENGTH 8

void setup();

//variables edited by interrupts
volatile char received;
volatile char i;
volatile char len;
char strbuf[STRBUFFER_LENGTH];

//constant strings to compare input to
const char* textOn = "led on";
#define ON_LENGTH 7
const char* textOff = "led off";
#define OFF_LENGTH 8

int main()
{
  setup();

  while(1){
    //check for "string received" flag
    if(received == -1){
      //reset flag then compare to desired string
      received = 0;
      if(len == ON_LENGTH && strncmp(strbuf, textOn, ON_LENGTH - 1) == 0) {
        //turn LED on 
        PORTB |= (1 << PIN_LED);
        continue;
      }
      if(len == OFF_LENGTH && strncmp(strbuf, textOff, OFF_LENGTH - 1) == 0) {
        //turn LED off
        PORTB &= ~(1 << PIN_LED);
        continue;
      }
    }

  }

}

void setup()
{
  uart_Init(9600);

  DDRB = (1 << PIN_LED); // set led's pin to output
  PORTB = (1 << PIN_BUTTON); //enable pull-up resistor for button

  cli(); //disable interrupts during setting up
  PCICR |= 1; //enable interrupts for port b
  PCMSK0 = (1 << PIN_BUTTON); //enable interrupt for button pin
  UCSR0B |= (1 << RXCIE0); //enable interrupt for rx
  sei(); //reenable interrupts
}

ISR(PCINT0_vect) //interrupt handler for button pin
{
    if((PINB & (1 << PIN_BUTTON)) == 0) uart_SendString("button pressed\n", 15);
}

ISR(USART_RX_vect) //interrupt handler for rx 
{
  received = UDR0;
  if(received == '\n'){
    len = i + 1;
    i = 0;
    received = -1;
  } else strbuf[i++] = received;

  if(i >= STRBUFFER_LENGTH) i = 0;
}