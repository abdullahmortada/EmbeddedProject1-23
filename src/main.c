#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "uart.h"
#include "dio.h"
#include "main.h"

//variables edited by interrupts
char strbuf[STRBUFFER_LENGTH];
volatile char received;
volatile int16_t i;

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
  cli(); //disable interrupts during setting up
  uart_Init(9600);
  uart_EnableRXInterrupt();

  dio_SetDirection(PORT_LED, PIN_LED, OUTPUT);
  dio_SetDirection(PORT_BUTTON, PIN_BUTTON, INPUT_PULLUP);

  dio_SetDirection('p', PCIE0, INTERRUPT_REG); //enable interrupts for port b
  dio_SetDirection('b', PIN_BUTTON, INTERRUPT_REG); //enable interrupt for button pin
  sei(); //reenable interrupts
}

