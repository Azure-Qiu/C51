#include "public.h"
#include "uart.h"
/** 
 **  @brief    ���ڻ���ʵ��
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


// �����жϷ�����ģ��
void UART_serve() interrupt 4{
	// �����ս����ж�ʱ
	if(RI){
		RI = 0; // �����־λ
		Uart_sendByte(SBUF); // ת��
	}
}




