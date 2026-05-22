#ifndef UART_H
#define UART_H

void UART_Init();
void UART_SendByte(unsigned char byte);
unsigned char UART_ReceiveByte();
void UART_SendString(const char *str);
void UART_SendNumber(unsigned int num);

#endif
