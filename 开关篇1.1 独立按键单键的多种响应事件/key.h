#ifndef __KEY_H__
#define __KEY_H__

#include "delay.h"


// 按键单次响应（0）或连续响应（1）开关
#define KEY1_MODE 0
#define KEY2_MODE 0
#define KEY3_MODE 0
#define KEY4_MODE 1

// 引脚定义
sbit key1 = P3^1; 
sbit key2 = P3^0;
sbit key3 = P3^2;
sbit key4 = P3^3;

// 按键状态枚举
typedef enum{
	KEY_UNPRESS = 0,
	KEY1_PRESS,
	KEY2_PRESS,
	KEY3_PRESS,
	KEY4_PRESS,
	KEY_NON_DEAL,
}Key_State;


void scan_key();
void check_key();

#endif