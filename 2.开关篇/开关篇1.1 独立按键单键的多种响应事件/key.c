#include "key.h"
#include "led.h"
#include "smg.h"
/** 
 **  @brief    独立按键的函数封装
 **  @author   QIU
 **  @date     2023.08.23
 **/

/*-------------------------------------------------------------------*/

// 按键状态、前状态
Key_State key_state, key_pre_state;

// 按键累积值，反映按键时长
u16 num = 0;


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
	}
}


/**
 **  @brief   （轮询方式）扫描独立按键，判断哪个键按下
 **  @param   无
 **  @retval  无
 **/
void scan_key(){
	static u8 flag = 1; // 开关（按下至完全松开为一轮判断）

	// 如果有按键按下
	if(flag && (!key1||!key2||!key3||!key4)){
		flag = 0; // 清零
		delay_ms(10); // 延时10ms消抖
		// key1往下屏蔽（屏蔽组合键）
		if(!key1) key_state = KEY1_PRESS; 
		else if(!key2) key_state = KEY2_PRESS;
		else if(!key3) key_state = KEY3_PRESS;
		else if(!key4) key_state = KEY4_PRESS;
		else key_state = KEY_UNPRESS;
	// 如果按键松开
	}else if(key1 && key2 && key3 && key4){
		flag = 1;
		delay_ms(10); // 延时10ms消抖,松开响应有逻辑判断时，需要加上消抖。否则可以省略。
		if(key1&&key2&&key3&&key4)key_state = KEY_UNPRESS;
	}
}



/**
 **  @brief   （轮询方式）判断按键, 进行相应处理
 **  @param    无
 **  @retval   无
 **/
void check_key(){
	switch(key_state){
		case KEY_UNPRESS:
			// 松开响应
			key_unpress();
			// 记录当前按键状态
			key_pre_state = KEY_UNPRESS;
			break;
		
		case KEY1_PRESS:
			// 记录当前按键状态
			key_pre_state = KEY1_PRESS;
			// 如果是单次响应
			if(!KEY1_MODE) key_state = KEY_NON_DEAL;
			key1_pressed();
			break;
		
		case KEY2_PRESS:
			// 记录当前按键状态
			key_pre_state = KEY2_PRESS;
			// 如果是单次响应
			if(!KEY2_MODE) key_state = KEY_NON_DEAL;
			key2_pressed();
			break;
		
		case KEY3_PRESS:
			// 记录当前按键状态
			key_pre_state = KEY3_PRESS;
			// 如果是单次响应
			if(!KEY3_MODE) key_state = KEY_NON_DEAL;
			key3_pressed();
			break;
		
		case KEY4_PRESS:
			// 记录当前按键状态
			key_pre_state = KEY4_PRESS;
			if(!KEY4_MODE) key_state = KEY_NON_DEAL;
			key4_pressed();
			break;
		
		case KEY_NON_DEAL:
			// 按下不处理
			break;
	}
}

