#include "delay.h"
/** 
 **  @brief    双色灯闪烁
 **  @author   QIU
 **  @data     2023.09.22
 **/

/*-------------------------------------------------------------------*/
#define DOUBLE_LED_PORT P2

sbit Green_LED = DOUBLE_LED_PORT^0;
sbit Red_LED = DOUBLE_LED_PORT^1;



void main(){

	while(1){
		Green_LED = 0;
		Red_LED = 1;
		delay_ms(500);
		Green_LED = 1;
		Red_LED = 0;
		delay_ms(500);
		
	}
}
