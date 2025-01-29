#ifndef __KEY_H__
#define __KEY_H__

#include "delay.h"

// 按键单次响应（0）或连续响应（1）开关，针对长按事件
#define KEY1_MODE 0
#define KEY2_MODE 0
#define KEY3_MODE 0
#define KEY4_MODE 1
#define KEY_1_2_MODE 0
#define KEY_1_3_MODE 0
#define KEY_1_4_MODE 0
#define KEY_2_3_MODE 0
#define KEY_2_4_MODE 0
#define KEY_3_4_MODE 1

// 按键时长（短按、长按分界）
# define KEY_DOWN_DURATION	300
// 双击时长（单击、双击分界），从第一次短按松开开始计算。取0时退化为单击
# define KEY_DOUBLE_DURATION  80


// 按键引脚定义
sbit key1 = P3^1; 
sbit key2 = P3^0;
sbit key3 = P3^2;
sbit key4 = P3^3;


// 按键基础状态枚举(低四位可表示4个独立按键)
typedef enum{
	KEY_UNPRESS = 0x00,  // 0000 0000
	KEY1_PRESS = 0x01,   // 0000 0001
	KEY2_PRESS = 0x02,   // 0000 0010
	KEY3_PRESS = 0x04,   // 0000 0100
	KEY4_PRESS = 0x08,   // 0000 1000
	KEY1_2_PRESS = 0x03, // 0000 0011
	KEY1_3_PRESS = 0x05, // 0000 0101
	KEY1_4_PRESS = 0x09, // 0000 1001
	KEY2_3_PRESS = 0x06, // 0000 0110
	KEY2_4_PRESS = 0x0A, // 0000 1010
	KEY3_4_PRESS = 0x0C, // 0000 1100
}Key_State;


// 按键事件模式枚举(最低位表示按键长短事件，次低位表示按键双击单击事件)
typedef enum{
	FREE_MODE = 0xff,      	   	  // 按键模式待确定阶段
	SHORT_PRESS = 0x00,    		  // 0000 0000
	LONG_PRESS = 0x01,     		  // 0000 0001
	DOUBLE_CLICK = 0x02,   		  // 0000 0010
}Key_Mode;



// 外部声明时，尽量带上数据类型，否则会产生重复定义的错误
extern Key_State key_state;


void scan_key();
void check_key();
void scan_double_click();
void scan_key_ByTimer();

#endif