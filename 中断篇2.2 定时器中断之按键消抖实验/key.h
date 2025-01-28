#ifndef __KEY_H__
#define __KEY_H__

#include "delay.h"

// 按键单次响应（0）或连续响应（1）开关
#define KEY3_MODE 1

// 按键引脚定义
sbit key3 = P3^2;


// 按键基础状态枚举(低四位可表示4个独立按键)
typedef enum{
	KEY_UNPRESS = 0x00,  // 0000 0000
	KEY3_PRESS = 0x04,   // 0000 0100
}Key_State;



// 外部声明时，尽量带上数据类型，否则会产生重复定义的错误
extern Key_State key_state;

void check_key();
void scan_key_ByTimer();

#endif