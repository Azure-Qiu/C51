#include "WS2812.h"
/** 
 **  @brief    WS2812驱动程序（@24M）
 **  @author   QIU
 **  @date     2024.04.01
 **/

/*-------------------------------------------------------------------*/

// 用于存放所有WS2812的RGB数据，二维数组
xdata u8 WS2812_Array[LED_MAX_NUM][3] = {0};



/**
 **  @brief   Reset信号，大于50us
 **  @param   参数说明
 **  @retval  返回值
 **/
void WS2812_Reset(){
	DI = 0;
	delay_10us(5);
}


/**
 **  @brief   设置指定灯的颜色（更改颜色数组）
 **  @param   参数说明
 **  @retval  返回值
 **/
void WS2812_Set_RGB(u8 num, u8 red, u8 green, u8 blue){ 
	// 设置
	WS2812_Array[num-1][0] = red;
	WS2812_Array[num-1][1] = green;
	WS2812_Array[num-1][2] = blue;
}



/**
 **  @brief   清除指定灯的颜色（更改颜色数组）
 **  @param   参数说明
 **  @retval  返回值
 **/
void WS2812_Clear_RGB(u8 num){ 
	// 清空
	memset(WS2812_Array[num-1], 0, sizeof(WS2812_Array[0]));
}



/**
 **  @brief   清屏
 **  @param   无
 **  @retval  无
 **/
void WS2812_Clear_All(){
	memset(WS2812_Array, 0, sizeof(WS2812_Array));
	WS2812_Update_RGB();
}



/**
 **  @brief   逻辑0和1的时序
 **  @param   参数说明
 **  @retval  返回值
 **/
void WS2812_Write_0_1(u8 dat){
	if(dat){
		DI = 1; // 800ns±150ns
		_nop_();
		DI = 0; // 450ns±150ns
	}else{
		DI = 1; // 450ns±150ns
		DI = 0; // 800ns±150ns
	}
}


/**
 **  @brief   发送单个灯的RGB值
 **  @param   参数说明
 **  @retval  返回值
 **/
void WS2812_Send_RGB(u8 *rgb){
	u8 green, red, blue;
	red = rgb[0];
	green = rgb[1];
	blue = rgb[2];
	// 发送G
	WS2812_Write_0_1(green & 0x80);WS2812_Write_0_1(green & 0x40);WS2812_Write_0_1(green & 0x20);WS2812_Write_0_1(green & 0x10);
	WS2812_Write_0_1(green & 0x08);WS2812_Write_0_1(green & 0x04);WS2812_Write_0_1(green & 0x02);WS2812_Write_0_1(green & 0x01);
	// 发送R
	WS2812_Write_0_1(red & 0x80);WS2812_Write_0_1(red & 0x40);WS2812_Write_0_1(red & 0x20);WS2812_Write_0_1(red & 0x10);
	WS2812_Write_0_1(red & 0x08);WS2812_Write_0_1(red & 0x04);WS2812_Write_0_1(red & 0x02);WS2812_Write_0_1(red & 0x01);
	// 发送B
	WS2812_Write_0_1(blue & 0x80);WS2812_Write_0_1(blue & 0x40);WS2812_Write_0_1(blue & 0x20);WS2812_Write_0_1(blue & 0x10);
	WS2812_Write_0_1(blue & 0x08);WS2812_Write_0_1(blue & 0x04);WS2812_Write_0_1(blue & 0x02);WS2812_Write_0_1(blue & 0x01);
}



/**
 **  @brief   发送所有灯的RGB值, 单次刷新。
 **  @param   参数说明
 **  @retval  返回值
 **/
void WS2812_Update_RGB(){
	u8 i;
	// 复位信号
	WS2812_Reset();
	
	for(i=0;i<LED_MAX_NUM;i++){
		WS2812_Send_RGB(WS2812_Array[i]);
	}
}


/**
 **  @brief   流水灯（逐一点亮）
 **  @param   red: 红色分量数组
 **			  green: 绿色分量数组
 **			  blue: 蓝色分量数组
 **			  speed: 控制延时时长（ms）
 **  @retval  返回值
 **/
void WS2812_Stream_Mode(u8 *red, u8 *green, u8 *blue, u16 speed){
	u8 i;
	for(i=0;i<LED_MAX_NUM;i++){
		WS2812_Set_RGB(i+1, red[i], green[i], blue[i]);
		WS2812_Update_RGB();
		delay_ms(speed);
	}
	WS2812_Clear_All();
}

