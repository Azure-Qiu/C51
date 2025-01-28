#ifndef _PUBLIC_H_
#define _PUBLIC_H_

/*---------------------常用头文件---------------------------------*/
#include <REGX52.H>
#include <intrins.h>

#include <stdio.h>
#include <math.h>
#include <string.h>


#define false 0
#define true 1

typedef unsigned char u8;
typedef unsigned int u16;

void delay_10us(u16);
void delay_ms(u16);

u8 * int2String(int, bit);
u8 * float2String(float, u8);

#endif
