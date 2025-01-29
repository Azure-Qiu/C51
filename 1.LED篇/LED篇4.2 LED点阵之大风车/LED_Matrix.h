#ifndef _LED_MATRIX_
#define _LED_MATRIX_

#include "delay.h"

#define LED_PORT P0

sbit SER = P3^4; // 串行输入
sbit ST = P3^5; // 存储寄存器时钟引脚
sbit SH = P3^6; // 移位存储器时钟引脚

void LED_Init(void);
void LED_Animation_Show(u8, u8);

#endif