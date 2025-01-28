#include "matrix_key.h"

/** 
 **  @brief    实现了矩阵按键的两种扫描方式
 **            1. 实现了延时法和定时器法两种刷新方式
 **  @author   QIU
 **  @date     2024.02.18
 **/


/*-------------------------------------------------------------------*/

// 存储按下的行列
u8 row, col;
// 按键事件处理状态，true已处理，false未处理
u8 key_is_dealed = false;

// 键值对应显示数值
u8 key_val = 0; 

// 反转法状态机
Turn_State turn_state = COL_Test;



/**
 **  @brief   读取电平
 **  @param   state: 0-列，1-行
 **  @retval  返回列（行）数
 **/
u8 read_port(bit state){
	u8 dat;
	if(state) dat = MATRIX_PORT >> 4; // 如果是行，取高四位
	else dat =  MATRIX_PORT & 0x0f;   // 如果是列，取低四位
	// 从左上开始为第一行，第一列
	switch(dat){
		// 0000 1110 第4列(行)
		case 0x0e: return 4;
		// 0000 1101 第3列(行)
		case 0x0d: return 3;
		// 0000 1011 第2列(行)
		case 0x0b: return 2;
		// 0000 0111 第1列(行)
		case 0x07: return 1;
		// 0000 1111 没有按下
		case 0x0f: return 0xff;
		// 多键同时按下不响应
		default: return 0;
	}
}



/**
 **  @brief   矩阵按键处理函数
 **  @param   参数说明
 **  @retval  返回值
 **/
void key_pressed(){
	// 如果不是连续模式，则按键事件标记为已处理
	if(!MatrixKEY_MODE) key_is_dealed = true; 
	// 计算器处理函数
	calculator_deal_key(row, col);
}



/**
 **  @brief   (反转法)检测按键（单键），按住过程中屏蔽其他按键。同列需全部松开才能再次响应
 **  @param   无
 **  @retval  无
 **/
void check_matrixKey_turn(){
	// 所有行置低电平，列置高电平
	MATRIX_PORT = 0x0f;
	// 读取所有列电平
	col = read_port(0);
	// 如果按键松开
	if(col == 0xff) {key_is_dealed = false; return;}
	// 如果有效键按下，延时消抖
	else if(col && !key_is_dealed) delay_ms(10);
	else return; 
	// 所有列置低电平，行置高电平
	MATRIX_PORT = 0xf0;
	// 读取所有行电平
	row = read_port(1);
	// 如果有键按下，响应
	if(row && row != 0xff) key_pressed();
	else return;
}


/**
 **  @brief   (扫描法)检测按键，本例扫描列
 **  @param   无
 **  @retval  无
 **/
void check_matrixKey_scan(){
	u8 i;
	for(i=0;i<4;i++){
		MATRIX_PORT = ~(0x08>>i); // 逐列置0，且所有行置1
		row = read_port(1); // 读取行
		// 保证之前记录按下的列为当前扫描列
		if(!row && col == i+1) continue; // 当前扫描列无有效键按下
		else if(row == 0xff && col == i+1) {key_is_dealed = false; continue;}
		else if(row && !key_is_dealed){       // 有效键按下且为未处理状态
			delay_ms(10);
			row = read_port(1); // 再次读取行
			if(row && row != 0xff) {col = i+1;key_pressed();} 
		}
	}
}


/**
 **  @brief   (反转法)采用定时器
 **  @param   参数说明
 **  @retval  返回值
 **/
void check_matrixKey_turn_ByTimer(){
	static u8 counter = 0;
	switch(turn_state){
		case COL_Test:
			// 所有行置低电平，列置高电平
			MATRIX_PORT = 0x0f;
			// 读取所有列电平
			col = read_port(0);
			// 如果按键未按下（已松开）
			if(col == 0xff) {key_is_dealed = false; break;}
			// 如果有效键按下，且按键未处理时，状态流转
			else if(col && !key_is_dealed) turn_state = Filter;
			break;
		case Filter:
			counter++;
			// 一般定时1ms，即过滤10ms防抖
			if(counter >= 10){
				counter = 0; 
				turn_state = ROW_Test;
			}
			break;
		case ROW_Test:
			// 所有列置低电平，行置高电平
			MATRIX_PORT = 0xf0;
			// 读取所有行电平
			row = read_port(1);
			// 如果有键按下，响应
			if(row && row != 0Xff) key_pressed();
			// 状态流转
			turn_state = COL_Test;
			break;
	}
}



/**
 **  @brief   (扫描法)采用定时器
 **  @param   无
 **  @retval  无
 **/
void check_matrixKey_scan_ByTimer(){
	static u8 i, counter;

	// 开始滤抖
	if(counter){
		if(counter > 10){
			counter = 0;
			row = read_port(1); // 再次读取行
			if(row && row != 0xff) {col = i+1; key_pressed();}
		}else{
			counter++;
		}
	}else{
		MATRIX_PORT = ~(0x08>>i); // 逐列置0，且所有行置1
		row = read_port(1); // 读取行
		// 保证之前记录按下的列为当前扫描列
		if(row == 0xff && col == i+1) {key_is_dealed = false;}
		else if(row && row != 0xff && !key_is_dealed) {counter++; return;} // 有效键按下且为未处理状态
		
		i++;
		if(i >= 4) i = 0;
	}
}


