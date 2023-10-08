#ifndef _uart_
#define _uart_

void uart_SetBaudRate(unsigned long baud);

void uart_Init(unsigned long baud);

void uart_Transmit(unsigned char data);

unsigned char uart_Receive(void);

void uart_SendString(char * String, unsigned int length);
#endif
