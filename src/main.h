#ifndef __main__ 
#define __main__ 

#include <stdint.h>

#define PIN_BUTTON 4
#define PORT_BUTTON 'b'
#define PIN_LED 5
#define PORT_LED 'b' 
#define STRBUFFER_LENGTH 8

#define textOn "led on"
#define ON_LENGTH 6
#define textOff "led off"
#define OFF_LENGTH 7

extern char strbuf[STRBUFFER_LENGTH];
extern volatile char received;
extern volatile int16_t i;

void setup();

#endif 
