#ifndef DIO 
#define DIO 

#include <stdint.h>

#define INPUT 0
#define OUTPUT 1 
#define INPUT_PULLUP 2
#define DIRECTION 3

void dio_SetDirection(char reg, uint8_t pin , uint8_t direction);

void dio_SetPin(char reg, uint8_t pin, uint8_t val);

uint8_t dio_GetPin(char reg, uint8_t pin);

void dio_SetInputReg(char reg, uint8_t pin, uint8_t direction);

void dio_SetOutputReg(char reg, uint8_t pin);

uint8_t BitToBitmask(char bit);

volatile uint8_t* CharToPort(char reg, uint8_t ddrOrPort);
#endif 
