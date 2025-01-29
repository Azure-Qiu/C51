#ifndef __WS2812_H__
#define __WS2812_H__


#include "public.h"


// 可级联的最大数量
#define LED_MAX_NUM 8

sbit DI = P2^1;

extern xdata u8 WS2812_Array[LED_MAX_NUM][3];




void WS2812_Set_RGB(u8 num, u8 red, u8 green, u8 blue);
void WS2812_Clear_All();
void WS2812_Update_RGB();

void WS2812_Stream_Mode(u8 *red, u8 *green, u8 *blue, u16 speed);

#endif