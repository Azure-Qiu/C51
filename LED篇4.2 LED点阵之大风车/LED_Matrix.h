#ifndef _LED_MATRIX_
#define _LED_MATRIX_

#include "delay.h"

#define LED_PORT P0

sbit SER = P3^4; // ��������
sbit ST = P3^5; // �洢�Ĵ���ʱ������
sbit SH = P3^6; // ��λ�洢��ʱ������

void LED_Init(void);
void LED_Animation_Show(u8, u8);

#endif