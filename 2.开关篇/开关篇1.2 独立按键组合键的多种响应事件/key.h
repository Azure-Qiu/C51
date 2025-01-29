#ifndef __KEY_H__
#define __KEY_H__

#include "public.h"

// 按键单次响应（0）或连续响应（1）开关
#define KEY1_MODE 0
#define KEY2_MODE 0
#define KEY3_MODE 0
#define KEY4_MODE 1
#define KEY_1_2_MODE 0
#define KEY_2_3_MODE 0
#define KEY_3_4_MODE 1

// 引脚定义
sbit key1 = P3^1; 
sbit key2 = P3^0;
sbit key3 = P3^2;
sbit key4 = P3^3;

// 按键状态枚举
typedef enum{
	KEY_UNPRESS = 0,
	KEY1_PRESS = 0x01,
	KEY2_PRESS = 0x02,
	KEY3_PRESS = 0x04,
	KEY4_PRESS = 0x08,
	KEY1_2_PRESS = 0x03,
	KEY2_3_PRESS = 0x06,
	KEY3_4_PRESS = 0x0C,
	KEY_NON_DEAL = 0xff,
}Key_State;


void scan_key();
void check_key();

#endif