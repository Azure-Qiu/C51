#include "LED_Matrix.h"
#include "timer.h"


void main(){
	LED_Matrix_Init();
	TIMERx_init(0, 922);
	TR0 = 1;
	while(1){
		// LED_Matrix_Flush_Delay();
	}
}

// ��ʱ��0���жϷ������ģ��
void TIMER0_serve() interrupt 1{
	TL0 = (65536-922)%256; //��8λ
	TH0 = (65536-922)/256; //��8λ
	
	LED_Matrix_Flush_Timer();
}
	
	