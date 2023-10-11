#include <avr/io.h>
#include "dio.h"

void dio_SetDirection(char reg, uint8_t pin, uint8_t direction){
  //get register pointer from initial and desired direction
  volatile uint8_t *regPointer = CharToPort(reg, DIRECTION_REG);

  if (regPointer == 0) return; //0 means no valid register

  switch(direction){
    case INPUT:
      *regPointer &= ~BitToBitmask(pin);
      return;

    case INPUT_PULLUP:
      *regPointer &= ~BitToBitmask(pin);
      regPointer = CharToPort(reg, OUTPUT);
      *regPointer |= BitToBitmask(pin);
      return;

    case OUTPUT:
      *regPointer |= BitToBitmask(pin);
      return;

    case INTERRUPT_REG:
      regPointer = CharToPort(reg, direction);
      *regPointer |= BitToBitmask(pin);
      return;

  }
} 


void dio_SetPin(char reg, uint8_t pin, uint8_t val){
  //get register pointer from initial and desired direction
  volatile uint8_t *regPointer = CharToPort(reg, OUTPUT);

  if(regPointer == 0) return; //0 means no valid register

  //set or clear bit at "pin" in PORTX register depending on "val"
  if (val == 0) *regPointer &= ~BitToBitmask(pin);
  else *regPointer |= BitToBitmask(pin);
}


uint8_t dio_GetPin(char reg, uint8_t pin){
  //get register pointer from initial and desired direction
  volatile uint8_t *regPointer = CharToPort(reg, INPUT);
  
  if (regPointer == 0) return 2;

  return *regPointer & BitToBitmask(pin); 
}


void dio_EnableRXInterrupt(){UCSR0B |= (1 << RXCIE0);}
void dio_EnableTXInterrupt(){UCSR0B |= (1 << TXCIE0);}


volatile uint8_t* CharToPort(char reg, uint8_t ddrOrPort){
  //return address to the desired register casted as a pointer 
  switch(reg){
    case 'b':
      if (ddrOrPort == DIRECTION_REG) return ((volatile uint8_t*)0x24);
      if (ddrOrPort == OUTPUT) return ((volatile uint8_t*)0x25);
      if (ddrOrPort == INTERRUPT_REG) return ((volatile uint8_t*)0x6B);
      return ((volatile uint8_t*)0x23);

    case 'c':
      if (ddrOrPort == DIRECTION_REG) return ((volatile uint8_t*)0x27);
      if (ddrOrPort == OUTPUT) return ((volatile uint8_t*)0x28);
      if (ddrOrPort == INTERRUPT_REG) return ((volatile uint8_t*)0x6C);
      return ((volatile uint8_t*)0x26);

    case 'd':
      if (ddrOrPort == DIRECTION_REG) return ((volatile uint8_t*)0x2A);
      if (ddrOrPort == OUTPUT) return ((volatile uint8_t*)0x2B);
      if (ddrOrPort == INTERRUPT_REG) return ((volatile uint8_t*)0x6D);
      return ((volatile uint8_t*)0x29);

    case 'p':
      return ((volatile uint8_t*)0x68);

    default:
      return 0;
  }
}


uint8_t BitToBitmask(char bit){
  return 1 << bit;
}
