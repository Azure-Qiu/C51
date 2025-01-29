#include "delay.h"
#include "interrupt.h"
#include "led.h"
/** 
 **  @brief    以外部中断方式响应按键事件
 **  @author   QIU
 **  @data     2023.08.31
 **/

/*-------------------------------------------------------------------*/


// 定义引脚
sbit btn4 = P3^3;


void main(){
	INTx_init(1);
	while(1);
}


void INT1_serve() interrupt 2{
	if(btn4 == 0){
		delay_ms(10);
		// 按下消抖
		if(btn4 == 0){
			led_turn(1);
		}
	}
}


