#include "timer.h"
#include "interrupt.h"
#include "key.h"
/** 
 **  @brief    采用外部中断响应，定时器消抖结合的方式。实现单个按键功能demo
 **			   1. 实现按下响应：key3键按下，数码管数字持续增加，led1保持常亮
 **			   2. 实现松开响应：key3键松开，数码管数字归零，led1熄灭
 **  @author   QIU
 **  @data     2023.08.31
 **/

/*-------------------------------------------------------------------*/

// 定时器初值，延时1ms计算
u16 time_init = 922;


void main(){
	INTx_init(0);     // 中断0
	TIMERx_init(0, time_init); // 定时器0
	
	TR0 = 1; // 开启定时器0
	
	while(1){
		// 判断按键并处理
		check_key();
	}
}


// 外部中断0的中断服务程序模板
void INT0_serve() interrupt 0{
	// 更新按键状态标志
	key_state |= KEY3_PRESS;
}



// 定时器0的中断服务程序
void TIMER0_serve() interrupt 1{
	
	TL0 = (65536-time_init)%256; //低8位
	TH0 = (65536-time_init)/256; //高8位
	
	// 如果检测到实时按键按下
	if(key_state){
		// 开始检查确认按键实际状态，去抖
		scan_key_ByTimer();
	}
}



