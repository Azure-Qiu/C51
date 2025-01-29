#include "led.h"
#include "timer.h"
/** 
 **  @brief    仅提供一个demo
 **  @author   QIU
 **  @data     2023.08.23
 **/

/*-------------------------------------------------------------------*/
// 定时器初值
u16 time_init = 9216;
// 定时累积次数
u8 interval = 50; // 500ms

int main(void){
	TIMERx_init(0, time_init); // 定时器0，10ms
	TR0 = 1;
	// flag_led_stream = true;
	while(1){
		// 流水灯
		//led_stream(50000);  
		
		// 跑马灯
		// led_run(50000);  
	}
}

// 定时器0的中断服务程序模板
void TIMER0_serve() interrupt 1{
	static u8 counter;
	TL0 = (65536-time_init)%256; // 低8位
	TH0 = (65536-time_init)/256; // 高8位
	
//	// 测试流水灯（定时器版本）
//	if(counter >= interval && flag_led_stream){
//		counter = 0;
//		led_stream_byTimer();
//	}else{
//		counter++;
//	}
	// 测试跑马灯（定时器版本）
	if(counter >= interval){
		counter = 0;
		led_run_byTimer();
	}else{
		counter++;
	}
}



