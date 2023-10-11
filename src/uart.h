#ifndef _uart_
#define _uart_

#include <stdint.h>

void uart_SetBaudRate(uint64_t baud);

void uart_Init(uint64_t baud);

void uart_Transmit(uint8_t data);

void uart_SendString(char * String, uint32_t length);

uint8_t uart_Receive(void);
#endif
