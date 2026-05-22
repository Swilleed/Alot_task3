#ifndef UART_H
#define UART_H

void UART_Init(void);
void UART_SendByte(unsigned char byte);
void UART_SendString(const char *str);
void UART_SendNumber(unsigned int num);
unsigned char UART_CommandReady(void);
unsigned char *UART_GetCommand(void);

#endif
