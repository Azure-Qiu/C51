#include "public.h"
#include "uart.h"

/** 
 **  @brief    ʵ��printf�ض���
 **  @author   QIU
 **  @date     2024.03.10
 **/

/*-------------------------------------------------------------------*/

/**
 **  @brief   ��дprintf���õ�putchar�������ض��򵽴������
 **  @param   ����˵��
 **  @retval  ����ֵ
 **/
char putchar(char c){
	Uart_sendByte(c); // �ض��򵽴��ڵ��ֽ����
	return c;  // ���ظ������ĵ�����printf
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



