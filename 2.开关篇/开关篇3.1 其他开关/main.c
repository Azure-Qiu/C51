#include "interrupt.h"
/** 
 **  @brief    ����ʵ�飨�����ؽ���P3_2���ţ�ͨ���ⲿ�ж�INT0�����Լ�⿪���źţ�������led0��ʾ��
 **  @author   QIU
 **  @date     2024.04.06
 **/
/*-------------------------------------------------------------------*/

sbit LED_Port = P2^0;


int main(void){
	// ��ʼ��INT0
	INTx_init(0);
	while(1);
}

// �ⲿ�ж�0���жϷ������ģ��
void INT1_serve() interrupt 0{
	LED_Port = 0;
}