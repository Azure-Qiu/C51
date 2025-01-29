#include "key.h"
// 包含的头文件（按需求修改）
#include "led.h"
#include "smg.h"


/** 
 **  @brief    独立按键的函数封装
 **            1. 单键的短按与长按事件（长按事件分单次或连续响应）
 **            2. 单键的单击与双击事件
 **            3. 组合键的短按与长按事件
 **  @author   QIU
 **  @date     2024.02.07
 **/

/*-------------------------------------------------------------------*/

// 实时按键状态、当前确认状态、前确认状态
Key_State key_state, key_now_state, key_pre_state;
// 当前按键模式
Key_Mode key_mode = FREE_MODE;
// 双击标志
u8 Double_Click_flag = false;
// 双击最大延时计数器
u16 Double_Click_Counter = 0;

// 按键累积
u16 num = 0;
// LED流水灯速度
u16 led_speed = 10000;


/*------------------------按键响应函数定义区------------------------------*/


/**
 **  @brief   按键3短按，短按响应，在按键松开后判定执行
 **  @param   参数说明
 **  @retval  返回值
 **/
void key3_short_press(){
	led_turn(1);
}


/**
 **  @brief   按键3长按，按下响应
 **  @param   参数说明
 **  @retval  返回值
 **/
void key3_long_press(){
	led_run(led_speed);
}



/**
 **  @brief   按键3双击
 **  @param   参数说明
 **  @retval  返回值
 **/
void key3_double_click(){
	led_turn(2);
}


/**
 **  @brief   按键4短按，短按响应，在按键松开后判定执行
 **  @param   参数说明
 **  @retval  返回值
 **/
void key4_short_press(){
	led_turn(3);
}


/**
 **  @brief   按键4长按，按下响应
 **  @param   参数说明
 **  @retval  返回值
 **/
void key4_long_press(){
	led_stream(led_speed);
}



/**
 **  @brief   按键四双击
 **  @param   参数说明
 **  @retval  返回值
 **/
void key4_double_click(){
	led_turn(4);
}


/**
 **  @brief   按键3、4组合键，短按响应
 **  @param   参数说明
 **  @retval  返回值
 **/
void key3_4_combination(){
	led_turn(5);
}


/**
 **  @brief   按键3、4组合键，长按响应
 **  @param   参数说明
 **  @retval  返回值
 **/
void key3_4_long_combination(){
	num++;
	smg_showInt(num, 1);
}



/*--------------------------延时法按键检测-------------------------------*/



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
 **  @brief   双击事件检测
 **  @param   参数说明
 **  @retval  返回值
 **/
void scan_double_click(){
	if(Double_Click_flag){
		Double_Click_Counter++;
		// 如果已经超过了双击时间界线
		if(Double_Click_Counter >= KEY_DOUBLE_DURATION){
			// 上次短按视为单击事件
			key_mode = SHORT_PRESS;
			Double_Click_Counter = 0;
			Double_Click_flag = false;
		}
	}else{
		Double_Click_Counter = 0;
	}
}




/**
 **  @brief   （轮询方式）判断按键状态与模式, 进行相应处理
 **  @param    无
 **  @retval   无
 **/
void check_key(){
	
	// 检查按键模式
	switch(key_mode){
		case SHORT_PRESS:
			// 按键模式流转
			key_mode = FREE_MODE;
			// 短按只有松开响应，故考虑前状态
			// 短按均为单次响应
			switch(key_pre_state){
				case KEY1_PRESS:break;
				case KEY2_PRESS:break;
				case KEY3_PRESS:key3_short_press();break;
				case KEY4_PRESS:key4_short_press();break;
				case KEY1_2_PRESS:break;
				case KEY1_3_PRESS:break;
				case KEY1_4_PRESS:break;
				case KEY2_3_PRESS:break;
				case KEY2_4_PRESS:break;
				case KEY3_4_PRESS:key3_4_combination();break;
			}
			break;
		case LONG_PRESS:
			// 长按只有按下响应，故考虑当前状态
			// 长按分为单次响应和连续响应
			switch(key_now_state){
				case KEY1_PRESS:break;
				case KEY2_PRESS:break;
				case KEY3_PRESS:
					if(!KEY3_MODE) key_mode = FREE_MODE;
					key3_long_press();
					break;
				case KEY4_PRESS:
					if(!KEY4_MODE) key_mode = FREE_MODE;
					key4_long_press();
					break;
				case KEY1_2_PRESS:break;
				case KEY1_3_PRESS:break;
				case KEY1_4_PRESS:break;
				case KEY2_3_PRESS:break;
				case KEY2_4_PRESS:break;
				case KEY3_4_PRESS:
					// 按键模式流转
					if(!KEY_3_4_MODE) key_mode = FREE_MODE;
					key3_4_long_combination();
					break;
			}
			break;
		case DOUBLE_CLICK:
			key_mode = FREE_MODE;
			// 双击只有按下响应，故考虑当前状态
			// 双击只有单次响应
			switch(key_now_state){
				case KEY1_PRESS:break;
				case KEY2_PRESS:break;
				case KEY3_PRESS:key3_double_click();break;
				case KEY4_PRESS:key4_double_click();break;
				case KEY1_2_PRESS:break;
				case KEY1_3_PRESS:break;
				case KEY1_4_PRESS:break;
				case KEY2_3_PRESS:break;
				case KEY2_4_PRESS:break;
				case KEY3_4_PRESS:break;
			}
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
	static u16 counter = 0; 
	static u8 flag = 0xff;
	
	// 长按事件开关
	static bit flag_LongMode = true;
	// 双击事件开关
	static bit flag_DoubleClickMode = false;
	// 组合事件开关
	static bit flag_CombinationMode = false;

	
	flag <<= 1;

	if(key_state & KEY3_PRESS) flag |= key3; // 如果实时按键状态中包含键3，则检查键3引脚状态（按下为0）
	if(key_state & KEY4_PRESS) flag |= key4; // 如果实时按键状态中包含键4，则检查键4引脚状态（按下为0）
	
	switch(flag){
		case 0xff:
			// 连续8次检测到按键松开，视为松开状态。
			key_state &= ((~key3*KEY3_PRESS) | (~key4*KEY4_PRESS));
			// 按键状态更新
			key_pre_state = key_now_state;
			key_now_state = key_state;
		
			if(flag_DoubleClickMode){
				flag_DoubleClickMode = false;
			}else{
				if(flag_CombinationMode){
					// 解除屏蔽
					flag_CombinationMode = false;
				}else{
					// 如果小于阈值，则为短按操作
					if(counter < KEY_DOWN_DURATION){
						// 等待给定双击阈值，判断是否为双击事件
						Double_Click_flag = true;
						// 清零
						counter = 0;
					}else{
						// 长按只有按下响应
						key_mode = FREE_MODE;
						// 清零
						counter = 0;
						flag_LongMode = true;
					}
				}
			}
			// 如果键尚未完全松开，则剩余键被屏蔽
			if(key_now_state != KEY_UNPRESS) flag_CombinationMode = true;
			break;
		
		case 0x00:
			// 如果按键状态未变化
			if(key_state == key_now_state){
				if(flag_DoubleClickMode){
					// 如果是双击事件，则不再关心第二次单击所耗时长
					// 按住期间会屏蔽其他按键
				}else if(flag_CombinationMode){
					// 如果处于组合按键屏蔽的状态，不做响应
				}else{
					if(counter >= KEY_DOWN_DURATION){
						if(flag_LongMode){
							// 视为该键的长按模式
							flag_LongMode = false;
							key_mode = LONG_PRESS;
						}
					}else{
						counter++; // 开始计时
					}
				}
			}else{
				// 连续8次检测到按键按下，视为按下状态。
				// 如果按键动作相同且Double_Click_flag为真（即未超时），可视为双击事件
				if((key_state == key_pre_state) && Double_Click_flag){
					key_mode = DOUBLE_CLICK;
					flag_DoubleClickMode = true;
					Double_Click_flag = false;
				}else{
					// 重新计时（开始记录组合键时长）
					counter = 0;
				}
				// 更新按键状态
				key_pre_state = key_now_state;
				key_now_state = key_state;
			}	
			break;
	}
}

