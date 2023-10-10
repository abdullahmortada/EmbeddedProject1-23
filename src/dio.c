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
}

void dio_SetPin(char reg, uint8_t pin, uint8_t val){
  uint8_t *regPointer = CharToPort(reg, OUTPUT);

  if(regPointer == 0) return; 

  if (val == 0) *regPointer &= ~BitToBitmask(pin);
  else *regPointer |= BitToBitmask(pin);
}

uint8_t dio_GetPin(char reg, uint8_t pin){
  uint8_t *regPointer = CharToPort(reg, INPUT);
  
  if (regPointer == 0) return 2; 

  return *regPointer & BitToBitmask(pin);
}

void dio_SetInputReg(char reg, uint8_t pin, uint8_t direction){
  uint8_t *regPointer = CharToPort(reg, 0);

  if (regPointer == 0) return;
  *regPointer &= ~BitToBitmask(pin);

  if(direction == INPUT_PULLUP) {
    regPointer = CharToPort(reg, 1);
    *regPointer |= BitToBitmask(pin);
  }
}

void dio_SetOutputReg(char reg, uint8_t pin){
  uint8_t *regPointer = CharToPort(reg, 0);

  if (regPointer == 0) return;

  *regPointer |= BitToBitmask(pin);
}


uint8_t BitToBitmask(char bit){
  return 1 << bit;
}

uint8_t* CharToPort(char reg, uint8_t ddrOrPort){
  switch(reg){
    case 'b':
      if (ddrOrPort == DIRECTION) return *DDRB;
      if (ddrOrPort == OUTPUT) return *PORTB;
      return *PINB;

    case 'c':
      if (ddrOrPort == DIRECTION) return *DDRC;
      if (ddrOrPort == OUTPUT) return *PORTC;
      return *PINC;

    case 'd':
      if (ddrOrPort == DIRECTION) return *DDRD;
      if (ddrOrPort == OUTPUT) return *PORTD;
      return *PIND;

    default:
      return 0;
  }
}
