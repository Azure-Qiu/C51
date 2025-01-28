#include "delay.h"
/** 
 **  @brief    三色灯闪烁
 **  @author   QIU
 **  @data     2023.09.23
 **/

/*-------------------------------------------------------------------*/
#define THREE_LED_PORT P2

// 也可以单独赋值
sbit Green_LED = THREE_LED_PORT^0;
sbit Red_LED = THREE_LED_PORT^1;
sbit Blue_LED = THREE_LED_PORT^2;


void main(){
	u8 val = 0x01, i = 0;

	while(1){
		// 先清零
		THREE_LED_PORT = 0x00;
		// 再赋1
		THREE_LED_PORT |= (val<<i);
		i += 1;
		if(i >= 3){
			i = 0;
		}
		delay_ms(500);
	}
}
