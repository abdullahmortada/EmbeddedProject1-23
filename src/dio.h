#ifndef _dio_ 
#define _dio_ 

#include <stdint.h>

#define INPUT 0
#define OUTPUT 1 
#define INPUT_PULLUP 2
#define DIRECTION_REG 3
#define INTERRUPT_REG 4

#define PORTB_INTERRUPT PCINT0_vect
#define PORTC_INTERRUPT PCINT1_vect
#define PORTD_INTERRUPT PCINT2_vect

void dio_SetDirection(char reg, uint8_t pin , uint8_t direction);

void dio_SetPin(char reg, uint8_t pin, uint8_t val);

uint8_t dio_GetPin(char reg, uint8_t pin);

void dio_EnableRXInterrupt();
void dio_EnableTXInterrupt();

volatile uint8_t* CharToPort(char reg, uint8_t ddrOrPort);

uint8_t BitToBitmask(char bit);
#endif 
