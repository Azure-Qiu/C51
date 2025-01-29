#include "led.h"
/** 
 **  @brief    LED控制程序
 **  @author   QIU
 **  @data     2023.08.23
 **/

/*-------------------------------------------------------------------*/

// 控制定时器流水灯执行的开关
u8 flag_led_stream = false;


/**
 **  @brief  指定某个LED亮
 **  @param  pos: 位置(1~8)
 **  @retval 无
 **/
void led_on(u8 pos){
	LED_PORT &= ~(0x01<<(pos-1));
}


/**
 **  @brief  指定某个LED灭
 **  @param  pos: 位置(1~8)
 **  @retval 无
 **/
void led_off(u8 pos){
	LED_PORT |= 0x01<<(pos-1);
}


/**
 **  @brief   指定位置LED翻转
 **  @param   pos：1—8
 **  @retval  无
 **/
void led_turn(u8 pos){
	u8 port;
	port = (LED_PORT>>(pos-1)) & 0x01;
	if(port){
		led_on(pos);
	}else{
		led_off(pos);
	}
}


/**
 **  @brief   LED流水灯
 **  @param   time 延时时间
 **  @retval  无
 **/
void led_stream(u16 time){
	u8 i;
	for(i=0;i<8;i++){
		led_on(i+1);
		delay_10us(time);
	}
	
	// 全部熄灭
	for(i=0;i<8;i++){
		led_off(i+1);
	}
}


/**
 **  @brief   LED跑马灯
 **  @param   time 延时时间
 **  @retval  无
 **/
void led_run(u16 time){
	u8 i;
	for(i=0;i<8;i++){
		led_on(i+1);
		delay_10us(time);
		led_off(i+1);
	}
}



/**
 **  @brief   LED流水灯（定时器控制）
 **  @param   无
 **  @retval  无
 **/
void led_stream_byTimer(){
	static u8 pos = 1;
	u8 i;
	
	if(pos > 8){
		// 只执行一次
		// flag_led_stream = false;
		pos = 1;
		// 全部熄灭
		for(i=0;i<8;i++){
			led_off(i+1);
		}
	}else{
		led_on(pos);
		pos++;
	}
}


/**
 **  @brief   LED跑马灯（定时器控制）
 **  @param   无
 **  @retval  无
 **/
void led_run_byTimer(){
	static u8 pos = 1;
	
	if(pos == 1 || pos > 8){
		pos = 1;
		led_on(pos);
		led_off(8);
		pos++;
	}else{
		led_off(pos-1);
		led_on(pos);
		pos++;
	}
}

