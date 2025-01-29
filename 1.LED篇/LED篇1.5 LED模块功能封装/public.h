#ifndef _PUBLIC_H_
#define _PUBLIC_H_

/*---------------------常用头文件---------------------------------*/
#include <REGX52.H>
#include <intrins.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define false 0
#define true 1

// 两数最大值宏定义，需加括号防止运算符优先级问题
#define MAX(n,m) (n > m? n : m)

typedef unsigned char u8;
typedef unsigned int u16;

void delay_10us(u16);
void delay_ms(u16);

u8 * int2String(int, bit);
u8 * float2String(float, u8);

#endif
