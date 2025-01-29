#ifndef _SMG_H_
#define _SMG_H_

#include "delay.h"

#define SMG_PORT P0 
 
// 位选引脚，与38译码器相连
sbit A1 = P2^2;
sbit A2 = P2^3;
sbit A3 = P2^4;

void smg_showChar(u8, u8, bit);
void smg_showString(u8*, u8);
void smg_showInt(int, u8);
void smg_showFloat(double, u8, u8);

#endif
