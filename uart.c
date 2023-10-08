#include <avr/io.h>
#include "uart.h"

void uart_SetBaudRate(unsigned long baud){
  unsigned short ubrr = F_CPU/((baud*16UL) - 1); //baud rate formula
  UBRR0H = (ubrr >> 8); //4 msb
  UBRR0L = ubrr; //8 lsb
}

void uart_Init(unsigned long baud){
  uart_SetBaudRate(baud);

  UCSR0B |= (1 << RXEN0) | (1 << TXEN0); //enable uart transmit and receive
  UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); //set to 8-bit mode
}

void uart_Transmit(unsigned char data){
  int udr_empty;
  //wait for data register
  do{
    udr_empty = (UCSR0A & (1 << UDRE0)) != 0;
  } while (!udr_empty);

  UDR0 = data; //set data register 
}

void uart_SendString(char* String, unsigned int length){
  //loop over all the characters and transmit them one by one
  int i = 0;
  while(i < length) uart_Transmit(String[i++]);
}

unsigned char uart_Receive(){
  //wait for data register
  while((UCSR0A & (1 << RXC0)) == 0);
  return UDR0; //return received data

}
