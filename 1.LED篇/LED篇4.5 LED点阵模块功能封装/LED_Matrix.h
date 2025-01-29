#ifndef _LED_MATRIX_
#define _LED_MATRIX_

#include "public.h"

#define LED_Matrix_PORT P0
#define SPEED 300  // 动画速度
#define COL_NUM 1  // 每帧移动列数
#define LEN	sizeof(Animation_Array)/sizeof(Animation_Array[0]) - 8  // 动画数组长

sbit SER = P3^4; //串行输入
sbit ST = P3^5; //存储寄存器时钟引脚
sbit SH = P3^6; //移位存储器时钟引脚

void LED_Matrix_Init(void);
void LED_Matrix_Flush_Delay(void);
void LED_Matrix_Flush_Timer(void);

#endif