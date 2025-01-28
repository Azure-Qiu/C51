#include "MAX7219.h"
/** 
 **  @brief    MAX7219芯片驱动程序
 **  @author   QIU
 **  @date     2024.04.14
 **/
/*-------------------------------------------------------------------*/

// 引脚定义
sbit DI = P2^0;
sbit CS = P2^1;
sbit CLK = P2^2;

// 指令数组
u8 xdata Directives[5][2] = {
	{0x09, 0x00},
	{0x0A, 0x0f},
	{0x0B, 0x07},
	{0x0C, 0x01},
	{0x0F, 0x00},
};

/**
 **  @brief   MAX7219初始化
 **  @param   无
 **  @retval  无
 **/
void MAX7219_initial(){
	u8 i, j;
	
	for(i=0;i<5;i++){
		for(j=0;j<MATRIX_NUM;j++){
			MAX7219_write_data(Directives[i][0], Directives[i][1]);
		}
	}

//	MAX7219_write_data(0x09, 0x00); // 译码方式：不译码
//	MAX7219_write_data(0x0A, 0x0f); // 亮度调节：16级
//	MAX7219_write_data(0x0B, 0x07); // 扫描界限：扫描8列
//	MAX7219_write_data(0x0C, 0x01); // 关断模式：开启显示
//	MAX7219_write_data(0x0F, 0x00); // 显示测试：正常显示
}



/**
 **  @brief   写单字节数据
 **  @param   16位数据
 **  @retval  无
 **/
static void MAX7219_write_byte(u8 dat){
	u8 i;	
	for(i=0;i<8;i++){
		// 拉低时钟线
		CLK = 0;
		// 取高位
		DI = dat & 0x80;
		// 移位
		dat <<= 1;
		// 时钟上升沿
		CLK = 1;
	}
}



/**
 **  @brief   写数据
 **  @param   addr: 地址
 **  @param	  dat:  数据
 **  @retval  无
 **/
void MAX7219_write_data(u8 addr, u8 dat){
	// 拉低片选
	CS = 0;
	// 先发地址
	MAX7219_write_byte(addr);
	// 后发数据
	MAX7219_write_byte(dat);
	// 拉高片选
	CS = 1;
}










