#include "timer.h"
#include "interrupt.h"
#include "key.h"
/** 
 **  @brief    采用外部中断响应，定时器消抖结合的方式。实现按键功能的总体实现
 **			   1. 实现短按：key3键点亮led1，key4键点亮led3
 **			   2. 实现长按：key3键跑马灯，key4键流水灯
 **			   3. 实现双击：key3键点亮led2，key4键点亮led4
 **    		   4. 实现组合键：key3+key4短按点亮led5，长按数码管数字递增
 **  		   5. 实现按键屏蔽
 **  @author   QIU
 **  @data     2024.02.07
 **/

/*-------------------------------------------------------------------*/

// 定时器初值，延时1ms计算
u16 time_init = 922;



void main(){
	INTx_init(0);     // 中断0
	INTx_init(1);     // 中断1
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


// 外部中断1的中断服务程序
void INT1_serve() interrupt 2{
	// 更新按键状态标志
	key_state |= KEY4_PRESS;
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
	
	// 双击检测开启
	scan_double_click();


}



