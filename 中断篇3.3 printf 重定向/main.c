#include "public.h"
#include "uart.h"

/** 
 **  @brief    实现printf重定向
 **  @author   QIU
 **  @date     2024.03.10
 **/

/*-------------------------------------------------------------------*/

/**
 **  @brief   重写printf调用的putchar函数，重定向到串口输出
 **  @param   参数说明
 **  @retval  返回值
 **/
char putchar(char c){
	Uart_sendByte(c); // 重定向到串口单字节输出
	return c;  // 返回给函数的调用者printf
}


void main(void){
	u8 num = 1;
	u8 a[2] = {1,2};
	u8 *p = &num;
	Uart_Init(9600);
//	p++;
//	*p = 2;
//	p++;
//	*p = 3;
	printf("%bd,%p\r\n", num, &num); 
	printf("%bd,%p,%bd,%p\r\n", a[0],a,a[1],&a[1]); 
	printf("%d\r\n", (int)a[1]);
//	printf("%d\r\n", *(&num)); 
//	printf("%d\r\n", (int)1); 
	while(1);
}



