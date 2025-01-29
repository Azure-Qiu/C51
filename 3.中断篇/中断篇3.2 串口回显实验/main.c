#include "public.h"
#include "uart.h"
/** 
 **  @brief    串口回显实验
 **  @author   QIU
 **  @date     2024.03.10
 **/
 
 /*-------------------------------------------------------------------*/
 
 
void main(void){
	Uart_Init(9600);
	Uart_sendString("hello world!");
	Uart_sendFloat(3.141592653);
	Uart_sendInt(123456);
	while(1);
}


// 串口中断服务函数模板
void UART_serve() interrupt 4{
	// 当接收进入中断时
	if(RI){
		RI = 0; // 先清标志位
		Uart_sendByte(SBUF); // 转发
	}
}




