#include "LED_Matrix.h"
/** 
 **  @brief    封装了74HC595芯片的LED点阵代码
 **  @author   QIU
 **  @date     2023.08.23
 **/
/*-------------------------------------------------------------------*/

/**
 **  @brief   74HC595串转并驱动代码
 **  @param   dat:8位串行数据
 **  @retval  返回值：无
 **/
void LED_control(u8 dat){
	u8 i;
	// 将一个字节拆分成串行输入
	for(i=0;i<8;i++){
		SER = dat >> 7; // 先将最高位送入SER中
		dat <<= 1; // 左移1位(去掉最高位)更新数据
		SH = 0; // 给移位寄存器时序脉冲
		delay_10us(1);
		SH = 1; // 检测到上升沿时将SER数据读入移位寄存器中
		delay_10us(1);
	}
	ST = 0; // 当一个字节传输完毕，此时移位寄存器已满。给存储寄存器时序脉冲
	delay_10us(1);
	ST = 1; // 检测到上升沿时将移位寄存器中的8位数据全部读入存储寄存器中。通过并行输出引脚可以直接检测到
	delay_10us(1);
}

/**
 **  @brief   LED点阵初始化
 **  @param   无
 **  @retval  返回值：无
 **/
void LED_Init(void){
	LED_PORT = 0xff;
}



/**
  *  @brief 显示对应静态画面（8*8）
  *  @param datX：阴极，datY:阳极
  *  @retval
  */
void LED_Animation_Show(u8 datX, u8 datY){
	LED_control(datY); //阳极码
	LED_PORT = ~(0x80>>datX);
	delay_10us(100);
	LED_Init(); //消影
}
