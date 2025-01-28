#include "key.h"
// 包含的头文件（按需求修改）
#include "led.h"
#include "smg.h"
/** 
 **  @brief    独立按键的定时器实现
 **            1. 单键的按下响应与松开响应
 **            2. 单键的单次响应与连续响应
 **  @author   QIU
 **  @date     2023.08.31
 **/
 
/*-------------------------------------------------------------------*/

// 实时按键状态、当前确认状态、前确认状态
Key_State key_state, key_now_state, key_pre_state;
// 按键累积
u16 num = 0;


/*------------------------按键响应函数定义区------------------------------*/


/**
 **  @brief   按键3按键响应
 **  @param   参数说明
 **  @retval  返回值
 **/
void key3_press(){
	num++;
	smg_showInt(num, 1);
	led_on(1);
}



void key3_unpressed(){
	num = 0;
	smg_showChar('0', 1, false);
	led_turn(1);
}



/*--------------------------延时法按键检测------------------------------------*/

/**
 **  @brief   按键松开响应
 **  @param   无
 **  @retval  无
 **/
void key_unpress(){
	switch(key_pre_state){
		case KEY_UNPRESS: break;
		case KEY3_PRESS: key3_unpressed();break;
	}
}


#if 0

/**
 **  @brief   按键松开响应
 **  @param   无
 **  @retval  无
 **/
void key_unpress(){
	switch(key_pre_state){
		case KEY_UNPRESS: break;
		case KEY1_PRESS: key1_unpressed();break;
		case KEY2_PRESS: key2_unpressed();break;
		case KEY3_PRESS: key3_unpressed();break;
		case KEY4_PRESS: key4_unpressed();break;
		case KEY1_2_PRESS: key1_2_unpressed();break;
		case KEY2_3_PRESS: key2_3_unpressed();break;
		case KEY3_4_PRESS: key3_4_unpressed();break;
	}
}


/**
 **  @brief   （轮询方式）扫描独立按键，判断哪个键按下
 **  @param   无
 **  @retval  无
 **/
void scan_key(){
	static u8 flag = 1;

	// 如果有按键按下
	if(flag && (!key1||!key2||!key3||!key4)){
		flag = 0; // 清零
		delay_ms(10); // 延时10ms消抖
		delay_ms(50); // 延时50ms 容许间隔
		// 获取当前所有按下的键
		if(!key1) key_now_state |= KEY1_PRESS; 
		if(!key2) key_now_state |= KEY2_PRESS; 
		if(!key3) key_now_state |= KEY3_PRESS; 
		if(!key4) key_now_state |= KEY4_PRESS; 

	// 如果按键全部松开
	}else if(key1&&key2&&key3&&key4){
		flag = 1;
		delay_ms(10); // 延时10ms消抖,松开响应有逻辑判断时，需要加上消抖。否则可以省略。
		if(key1&&key2&&key3&&key4)key_now_state = 0;
	}
}



/**
 **  @brief   （轮询方式）判断按键, 进行相应处理
 **  @param    无
 **  @retval   无
 **/
void check_key(){
	switch(key_now_state){
		case KEY_UNPRESS:
			// 松开响应
			key_unpress();
			key_pre_state = KEY_UNPRESS;
			break;
		case KEY1_PRESS:
			key_pre_state = KEY1_PRESS;
			// 如果是单次响应
			if(!KEY1_MODE) key_now_state = KEY_NON_DEAL;
			key1_pressed();
			break;
		case KEY2_PRESS:
			key_pre_state = KEY2_PRESS;
			if(!KEY2_MODE) key_now_state = KEY_NON_DEAL;
			break;
		case KEY3_PRESS:
			key_pre_state = KEY3_PRESS;
			if(!KEY3_MODE) key_now_state = KEY_NON_DEAL;
			key3_pressed();
			break;
		case KEY4_PRESS:
			key_pre_state = KEY4_PRESS;
			if(!KEY4_MODE) key_now_state = KEY_NON_DEAL;
			key4_pressed();
			break;
		case KEY1_2_PRESS:
			key_pre_state = KEY1_2_PRESS;
			if(!KEY_1_2_MODE) key_now_state = KEY_NON_DEAL;
			key_1_2_pressed();
			break;
		case KEY2_3_PRESS:
			key_pre_state = KEY2_3_PRESS;
			if(!KEY_2_3_MODE) key_now_state = KEY_NON_DEAL;
			key_2_3_pressed();
			break;
		case KEY3_4_PRESS:
			key_pre_state = KEY3_4_PRESS;
			if(!KEY_3_4_MODE) key_now_state = KEY_NON_DEAL;
			key_3_4_pressed();
			break;
		case KEY_NON_DEAL:
			// 按下不处理
			break;
	}
}
#endif


/*---------------------------定时器法按键检测--------------------------------*/



/**
 **  @brief   （轮询方式）判断按键状态与模式, 进行相应处理
 **  @param    无
 **  @retval   无
 **/
void check_key(){
	static bit flag = true;
	// 检查按键模式
	switch(key_now_state){
		case KEY3_PRESS:
			// 按下响应
			if(flag) key3_press();
			// 按键模式流转
			if(!KEY3_MODE) flag = false;
			break;
		case KEY_UNPRESS:
			// 按下响应
			key_unpress();
			key_pre_state = KEY_UNPRESS;
			flag = true;
			break;
		default:
			break;
	}
	
}




/**
 **  @brief   （定时器）确认按键是否稳定按下/松开，去抖
 **  @param   无
 **  @retval  无
 **/
void scan_key_ByTimer(){
	static u8 flag = 0xff;
	
	flag <<= 1;

	flag |= key3; // 检查键3引脚状态（按下为0）
	
	switch(flag){
		case 0xff:
			// 连续8次检测到按键松开，视为松开状态。
			key_state = KEY_UNPRESS;
			// 按键状态更新
			key_pre_state = key_now_state;
			key_now_state = key_state;
			break;
		
		case 0x00:
			// 更新按键状态
			key_pre_state = key_now_state;
			key_now_state = key_state;
			break;
	}
}

