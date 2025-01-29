#ifndef __UART_H__
#define __UART_H__

#include "public.h"

void Uart_Init(u16);
void Uart_sendByte(u8);
void Uart_sendString(u8*);
void Uart_sendFloat(float);
void Uart_sendInt(long);
#endif