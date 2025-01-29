#include "matrix_key.h"
#include "beep.h"
#include "smg.h"
/** 
 **  @brief    实现了矩阵按键的两种扫描方式
 **			   1. 与数码管、蜂鸣器联动
 **			   2. 按下一个键，数码管显示对应（0~F）的数值
 **			   3. 按下至未松开过程中，屏蔽其他按键
 **  @author   QIU
 **  @date     2023.05.08
 **/


/*-------------------------------------------------------------------*/

// 存储按下的行列
u8 row, col;
// 按键当前状态，true按下中，false已释放
u8 key_now_state = false;


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
		case 0x0f: return 0;
		// 多键同时按下不响应
		default: return 0;
	}
}



/**
 **  @brief   矩阵按键处理
 **  @param   参数说明
 **  @retval  返回值
 **/
void key_pressed(){
	u8 key_val;
	// 如果不是连续模式
	if(!MatrixKEY_MODE) key_now_state = true; 
	// 蜂鸣器响应，第三行连接P1.5，不响
	beep_once(50, 2000);
	
	// 计算显示的字符
	key_val = (row-1)*4 + (col - 1);
	if(key_val >= 0 && key_val <= 9) key_val += '0';
	else key_val += 'A' - 10;
	// 字符显示
	smg_showChar(key_val, 1, false);
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
	// 如果有效键按下，延时消抖
	if(col) delay_ms(10);
	else {key_now_state = false;return;} // 注意，if else还是需要括号的，与case 不同
	// 所有列置低电平，行置高电平
	MATRIX_PORT = 0xf0;
	// 读取所有行电平
	row = read_port(1);
	// 如果有键按下(当前未按下)，响应
	if(row && !key_now_state) key_pressed();
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
		if(!row && col == i+1)key_now_state = false; // 当前扫描列无有效键按下
		else if(row && !key_now_state){       // 有效键按下且为松开状态
			delay_ms(10);
			row = read_port(1); // 再次读取行
			if(row) {col = i+1;key_pressed();} 
		}
	}
}
