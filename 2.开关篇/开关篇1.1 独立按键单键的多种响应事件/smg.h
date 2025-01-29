#ifndef _SMG_H_
#define _SMG_H_

#include "public.h"

#define SMG_PORT P0 
 
// 位选引脚，与38译码器相连
sbit A1 = P2^2;
sbit A2 = P2^3;
sbit A3 = P2^4;


void smg_showChar(u8, u8, bit);       // 静态字符显示函数
void smg_showString(u8*, u8);         // 动态字符串显示函数（延时法）
void smg_showInt(int, u8);            // 动态整数显示函数（延时法）
void smg_showFloat(double, u8, u8);   // 动态浮点数显示函数（延时法）

void smg_showString_Bytimer(u8*, u8); // 动态字符串显示函数（定时器法）

#endif