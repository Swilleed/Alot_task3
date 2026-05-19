#ifndef MCU_COMPAT_H
#define MCU_COMPAT_H

#include <STC89C5xRC.H>

sbit MCU_P00 = P0 ^ 0;
sbit MCU_P01 = P0 ^ 1;
sbit MCU_P02 = P0 ^ 2;
sbit MCU_P03 = P0 ^ 3;
sbit MCU_P04 = P0 ^ 4;
sbit MCU_P05 = P0 ^ 5;
sbit MCU_P06 = P0 ^ 6;
sbit MCU_P07 = P0 ^ 7;

sbit MCU_P10 = P1 ^ 0;
sbit MCU_P11 = P1 ^ 1;
sbit MCU_P12 = P1 ^ 2;
sbit MCU_P13 = P1 ^ 3;
sbit MCU_P14 = P1 ^ 4;
sbit MCU_P15 = P1 ^ 5;
sbit MCU_P16 = P1 ^ 6;
sbit MCU_P17 = P1 ^ 7;

sbit MCU_P20 = P2 ^ 0;
sbit MCU_P21 = P2 ^ 1;
sbit MCU_P22 = P2 ^ 2;
sbit MCU_P23 = P2 ^ 3;
sbit MCU_P24 = P2 ^ 4;
sbit MCU_P25 = P2 ^ 5;
sbit MCU_P26 = P2 ^ 6;
sbit MCU_P27 = P2 ^ 7;

sbit MCU_P30 = P3 ^ 0;
sbit MCU_P31 = P3 ^ 1;
sbit MCU_P32 = P3 ^ 2;
sbit MCU_P33 = P3 ^ 3;
sbit MCU_P34 = P3 ^ 4;
sbit MCU_P35 = P3 ^ 5;
sbit MCU_P36 = P3 ^ 6;
sbit MCU_P37 = P3 ^ 7;

#define P0_0 MCU_P00
#define P0_1 MCU_P01
#define P0_2 MCU_P02
#define P0_3 MCU_P03
#define P0_4 MCU_P04
#define P0_5 MCU_P05
#define P0_6 MCU_P06
#define P0_7 MCU_P07

#define P1_0 MCU_P10
#define P1_1 MCU_P11
#define P1_2 MCU_P12
#define P1_3 MCU_P13
#define P1_4 MCU_P14
#define P1_5 MCU_P15
#define P1_6 MCU_P16
#define P1_7 MCU_P17

#define P2_0 MCU_P20
#define P2_1 MCU_P21
#define P2_2 MCU_P22
#define P2_3 MCU_P23
#define P2_4 MCU_P24
#define P2_5 MCU_P25
#define P2_6 MCU_P26
#define P2_7 MCU_P27

#define P3_0 MCU_P30
#define P3_1 MCU_P31
#define P3_2 MCU_P32
#define P3_3 MCU_P33
#define P3_4 MCU_P34
#define P3_5 MCU_P35
#define P3_6 MCU_P36
#define P3_7 MCU_P37

#define P00 MCU_P00
#define P01 MCU_P01
#define P02 MCU_P02
#define P03 MCU_P03
#define P04 MCU_P04
#define P05 MCU_P05
#define P06 MCU_P06
#define P07 MCU_P07

#define P10 MCU_P10
#define P11 MCU_P11
#define P12 MCU_P12
#define P13 MCU_P13
#define P14 MCU_P14
#define P15 MCU_P15
#define P16 MCU_P16
#define P17 MCU_P17

#define P20 MCU_P20
#define P21 MCU_P21
#define P22 MCU_P22
#define P23 MCU_P23
#define P24 MCU_P24
#define P25 MCU_P25
#define P26 MCU_P26
#define P27 MCU_P27

#define P30 MCU_P30
#define P31 MCU_P31
#define P32 MCU_P32
#define P33 MCU_P33
#define P34 MCU_P34
#define P35 MCU_P35
#define P36 MCU_P36
#define P37 MCU_P37

#endif // MCU_COMPAT_H