#include <avr/io.h>
#include "dio.h"

void dio_SetDirection(char reg, uint8_t pin, uint8_t direction){
  //set pin direction depending on direction parameter
  if(direction == INPUT || direction == INPUT_PULLUP){
    dio_SetInputReg(reg, pin, direction);
    return;
  }

  if(direction == OUTPUT){
    dio_SetOutputReg(reg, pin);
  }
} 


void dio_SetInputReg(char reg, uint8_t pin, uint8_t direction){
  //get register pointer from initial and desired direction
  volatile uint8_t *regPointer = CharToPort(reg, DIRECTION_REG);

  if (regPointer == 0) return; //0 means no valid register

  //clear bit at "pin" in DDRX register for pin to be input
  *regPointer &= ~BitToBitmask(pin);

  //enable pullup resistor using PORTX registers
  if(direction == INPUT_PULLUP) {
    regPointer = CharToPort(reg, OUTPUT);
    *regPointer |= BitToBitmask(pin);
  }
}


void dio_SetOutputReg(char reg, uint8_t pin){
  //get register pointer from initial and desired direction
  volatile uint8_t *regPointer = CharToPort(reg, DIRECTION_REG);

  if (regPointer == 0) return; //0 means no valid register

  //set the bit at "pin" to enable output mode in DDRX register
  *regPointer |= BitToBitmask(pin);
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


volatile uint8_t* CharToPort(char reg, uint8_t ddrOrPort){
  //return address to the desired register casted as a pointer 
  switch(reg){
    case 'b':
      if (ddrOrPort == DIRECTION_REG) return ((volatile uint8_t*)0x24);
      if (ddrOrPort == OUTPUT) return ((volatile uint8_t*)0x25);
      return ((volatile uint8_t*)0x23);

    case 'c':
      if (ddrOrPort == DIRECTION_REG) return ((volatile uint8_t*)0x27);
      if (ddrOrPort == OUTPUT) return ((volatile uint8_t*)0x28);
      return ((volatile uint8_t*)0x26);

    case 'd':
      if (ddrOrPort == DIRECTION_REG) return ((volatile uint8_t*)0x2A);
      if (ddrOrPort == OUTPUT) return ((volatile uint8_t*)0x2B);
      return ((volatile uint8_t*)0x29);

    default:
      return 0;
  }
}


uint8_t BitToBitmask(char bit){
  return 1 << bit;
}
