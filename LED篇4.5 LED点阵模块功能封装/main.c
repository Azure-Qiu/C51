#include "LED_Matrix.h"
#include "timer.h"
/** 
 **  @brief    LED点阵功能封装
 **  @author   QIU
 **  @date     2023.08.23
 **/

int main(void){
	LED_Matrix_Init();
	TIMERx_init(0, 922);
	TR0 = 1;
	while(1){
//		LED_Matrix_Flush_Delay();
	}
}

// 定时器0的中断服务程序模板
void TIMER0_serve() interrupt 1{
	TL0 = (65536-922)%256; // 低8位
	TH0 = (65536-922)/256; // 高8位
	
	LED_Matrix_Flush_Timer();
}	
	