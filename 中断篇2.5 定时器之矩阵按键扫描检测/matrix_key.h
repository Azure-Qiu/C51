#ifndef _MATRIX_KEY_H_
#define _MATRIX_KEY_H_

#include "public.h"

#define MATRIX_PORT	P1

// 矩阵按键单次响应（0）或连续响应（1）开关
#define MatrixKEY_MODE 0


sbit ROW_PORT_1 = P1^7;
sbit ROW_PORT_2 = P1^6;
sbit ROW_PORT_3 = P1^5; // 共用了蜂鸣器引脚
sbit ROW_PORT_4 = P1^4;

sbit COL_PORT_1 = P1^3;
sbit COL_PORT_2 = P1^2;
sbit COL_PORT_3 = P1^1;
sbit COL_PORT_4 = P1^0;


// 对外声明键值
extern u8 key_val;


// 矩阵按键反转法状态机
typedef enum{
	COL_Test = 0,   // 列检测（空闲状态）
	Filter,         // 滤抖
	ROW_Test,       // 行检测
}Turn_State;


void check_matrixKey_turn();
void check_matrixKey_scan();
void check_matrixKey_turn_ByTimer();
void check_matrixKey_scan_ByTimer();

#endif