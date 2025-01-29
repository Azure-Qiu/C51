#include "key.h"
#include "led.h"
#include "smg.h"
#include <stdio.h>
/** 
 **  @brief    独立按键的函数封装
 **            1. 单键的单次或连续响应优化
 **            2. 组合键的单次或连续响应优化
 **  @author   QIU
 **  @date     2024.01.31
 **/

/*-------------------------------------------------------------------*/
// 按键状态、前状态
Key_State key_now_state, key_pre_state;

// 按键累积
u16 num = 0;
// LED速度
u16 led_speed = 10000;



/**
 **  @brief   按键1按下函数（可以按需求修改）
 **  @param   无
 **  @retval  无
 **/
void key1_pressed(){
	smg_showChar('1', 1, false);
	led_turn(6);
}


/**
 **  @brief   按键2按下函数（可以按需求修改）
 **  @param   无
 **  @retval  无
 **/
void key2_pressed(){
	;
}


/**
 **  @brief   按键3按下函数（可以按需求修改）
 **  @param   无
 **  @retval  无
 **/
void key3_pressed(){
	smg_showChar('3', 1, false);
	led_turn(8);
}


/**
 **  @brief   按键4按下函数（可以按需求修改）
 **  @param   无
 **  @retval  无
 **/
void key4_pressed(){
	u8 str[8];
	num++;
	sprintf(str,"%d",num/10);
	smg_showString(str, 1);
}


/**
 **  @brief   组合键1和2按下函数（可以按需求修改）
 **  @param   无
 **  @retval  无
 **/
void key_1_2_pressed(){
	smg_showChar('a', 1, false);
	led_stream(led_speed);
}


/**
 **  @brief   组合键2和3按下函数（可以按需求修改）
 **  @param   无
 **  @retval  无
 **/
void key_2_3_pressed(){
	smg_showChar('b', 1, false);
	led_run(led_speed);
}


/**
 **  @brief   组合键3和4按下函数（可以按需求修改）
 **  @param   无
 **  @retval  无
 **/
void key_3_4_pressed(){
	u8 str[8];
	led_speed += 100;
	sprintf(str,"%u",led_speed); // 无符号数
	smg_showString(str, 1);
}



/**
 **  @brief   按键1松开函数（可以按需求修改）
 **  @param   无
 **  @retval  无
 **/
void key1_unpressed(){
	;
}


/**
 **  @brief   按键2松开函数（可以按需求修改）
 **  @param   无
 **  @retval  无
 **/
void key2_unpressed(){
	smg_showChar('2', 1, false);
	led_turn(7);
}


/**
 **  @brief   按键3松开函数（可以按需求修改）
 **  @param   无
 **  @retval  无
 **/
void key3_unpressed(){
	key3_pressed();
}


/**
 **  @brief   按键4松开函数（可以按需求修改）
 **  @param   无
 **  @retval  无
 **/
void key4_unpressed(){
	smg_showChar('0', 1, false);
	num = 0;
}


/**
 **  @brief   按键1、2松开函数（可以按需求修改）
 **  @param   无
 **  @retval  无
 **/
void key1_2_unpressed(){
	;
}


/**
 **  @brief   按键2、3松开函数（可以按需求修改）
 **  @param   无
 **  @retval  无
 **/
void key2_3_unpressed(){
	;
}

/**
 **  @brief   按键3、4松开函数（可以按需求修改）
 **  @param   无
 **  @retval  无
 **/
void key3_4_unpressed(){
	;
}


/*-------------------------------------------------------------------*/


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

	// 如果有按键按下（按下过程中屏蔽其他按键，只有全部松开之后才再次检测）
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

