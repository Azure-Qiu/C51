#ifndef _MATRIX_KEY_H_
#define _MATRIX_KEY_H_

#include "delay.h"
#include "beep.h"
#include "smg.h"

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

void check_matrixKey_turn();
void check_matrixKey_scan();

#endif