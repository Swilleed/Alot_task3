#include <STC89C5xRC.H>
#include "UART.h"

#define RX_BUF_SIZE  32

static volatile unsigned char rx_buf[RX_BUF_SIZE];
static volatile unsigned char rx_idx;
static volatile unsigned char cmd_ready;
static volatile unsigned char tx_done;

/* 串口中断 ISR（中断号 4）*/
static void UART_ISR(void) interrupt 4
{
    unsigned char c;

    if (RI) {
        RI = 0;
        c = SBUF;

        if (c == '\r' || c == '\n') {
            if (rx_idx > 0) {
                rx_buf[rx_idx] = '\0';
                cmd_ready = 1;
            }
            rx_idx = 0;
        } else if (rx_idx < RX_BUF_SIZE - 1) {
            rx_buf[rx_idx++] = c;
        }
    }

    if (TI) {
        TI = 0;
        tx_done = 1;
    }
}

void UART_Init()
{
    SCON = 0x50;   // 模式1，允许接收
    TMOD |= 0x20;  // 定时器1模式2（自动重载）
    PCON |= 0x80;  // SMOD = 1（波特率加倍）
    TH1 = 0xFF;    // 57600 baud @ 11.0592MHz
    TL1 = 0xFF;
    TR1 = 1;       // 启动定时器1
    ES  = 1;       // 使能串口中断
}

unsigned char UART_CommandReady(void)
{
    return cmd_ready;
}

unsigned char *UART_GetCommand(void)
{
    cmd_ready = 0;
    return (unsigned char *)rx_buf;
}

void UART_SendByte(unsigned char byte)
{
    tx_done = 0;
    SBUF = byte;
    while (!tx_done)
        ;
}

void UART_SendString(const char *str)
{
    while (*str) {
        UART_SendByte(*str++);
    }
}

void UART_SendNumber(unsigned int num)
{
    char buf[6];
    unsigned char i = 5;
    buf[5] = '\0';
    do {
        buf[--i] = '0' + (num % 10);
        num /= 10;
    } while (num > 0);
    UART_SendString(buf + i);
}
