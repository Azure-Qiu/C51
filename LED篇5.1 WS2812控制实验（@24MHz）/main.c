#include "WS2812.h"
/** 
 **  @brief    WS2812驱动实验
 **  @author   QIU
 **  @date     2024.04.03
 **/

/*-------------------------------------------------------------------*/


u8 Red_Array[LED_MAX_NUM] = {
	255, 230, 200, 180, 150, 120, 100, 60
};
u8 Green_Array[LED_MAX_NUM] = {
	200, 30, 230, 80, 50, 20, 0, 160
};
u8 Blue_Array[LED_MAX_NUM] = {
	210, 120, 20, 140, 250, 220, 120, 80
};


int main(void){
	
//	WS2812_Stream_Mode(Red_Array, Green_Array, Blue_Array, 500);
	WS2812_Set_RGB(1, 0,0,0);
	WS2812_Update_RGB();
	while(1){
		
	}
}