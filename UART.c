#include <STC89C5xRC.H>

void UART_Init()
{
    SCON = 0x50;  // 设置串口工作模式1，允许接收
    TMOD |= 0x20; // 定时器1工作在模式2（自动重载）
    TH1 = 0xFD;   // 设置波特率为9600
    TL1 = 0xFD;   // 设置波特率为9600
    TR1 = 1;      // 启动定时器1
}

void UART_SendByte(unsigned char byte)
{
    SBUF = byte; // 将数据写入SBUF寄存器
    while (!TI)
        ;   // 等待发送完成
    TI = 0; // 清除发送完成标志
}

unsigned char UART_ReceiveByte()
{
    while (!RI)
        ;        // 等待接收完成
    RI = 0;      // 清除接收完成标志
    return SBUF; // 返回接收到的数据
}

void UART_SendString(const char *str)
{
    while (*str) {
        UART_SendByte(*str++); // 发送字符串中的每个字符
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
