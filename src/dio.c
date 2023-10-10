#include <avr/io.h>
#include "dio.h"

void dio_SetDirection(char reg, uint8_t pin, uint8_t direction){
  if(direction == INPUT || direction == INPUT_PULLUP){
    dio_SetInputReg(reg, pin, direction);
    return;
  }

  if(direction == OUTPUT){
    dio_SetOutputReg(reg, pin);
  }
} void dio_SetPin(char reg, uint8_t pin, uint8_t val){
  volatile uint8_t *regPointer = CharToPort(reg, OUTPUT);

  if(regPointer == 0) return; 

  if (val == 0) *regPointer &= ~BitToBitmask(pin);
  else *regPointer |= BitToBitmask(pin);
}

uint8_t dio_GetPin(char reg, uint8_t pin){
  volatile uint8_t *regPointer = CharToPort(reg, INPUT);
  
  if (regPointer == 0) return 2; 

  return *regPointer & BitToBitmask(pin);
}

void dio_SetInputReg(char reg, uint8_t pin, uint8_t direction){
  volatile uint8_t *regPointer = CharToPort(reg, DIRECTION);
  if (regPointer == 0) return;
  *regPointer &= ~BitToBitmask(pin);

  if(direction == INPUT_PULLUP) {
    regPointer = CharToPort(reg, OUTPUT);
    *regPointer |= BitToBitmask(pin);
  }
}

void dio_SetOutputReg(char reg, uint8_t pin){
  volatile uint8_t *regPointer = CharToPort(reg, DIRECTION);

  if (regPointer == 0) return;

  *regPointer |= BitToBitmask(pin);
}


uint8_t BitToBitmask(char bit){
  return 1 << bit;
}

volatile uint8_t* CharToPort(char reg, uint8_t ddrOrPort){
  switch(reg){
    case 'b':
      if (ddrOrPort == DIRECTION) return ((volatile uint8_t*)0x24);
      if (ddrOrPort == OUTPUT) return ((volatile uint8_t*)0x25);
      return ((volatile uint8_t*)0x23);

    case 'c':
      if (ddrOrPort == DIRECTION) return ((volatile uint8_t*)0x27);
      if (ddrOrPort == OUTPUT) return ((volatile uint8_t*)0x28);
      return ((volatile uint8_t*)0x26);

    case 'd':
      if (ddrOrPort == DIRECTION) return ((volatile uint8_t*)0x2A);
      if (ddrOrPort == OUTPUT) return ((volatile uint8_t*)0x2B);
      return ((volatile uint8_t*)0x29);

    default:
      return 0;
  }
}
