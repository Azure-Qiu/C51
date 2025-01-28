#include "LED_Matrix.h"
/** 
 **  @brief    LED点阵封装（74HC595芯片驱动代码）
 **  @author   QIU
 **  @data     2023.08.23
 **/

/*-------------------------------------------------------------------*/

// 画面帧（2022年12月30日）
u8 code Animation_Array[] = {
	0x61,0x83,0x85,0x89,0x71,0x00,0x7E,0x81,
	0x81,0x7E,0x00,0x61,0x83,0x85,0x89,0x71,
	0x00,0x61,0x83,0x85,0x89,0x71,0x00,0x44,
	0xDC,0x54,0x7F,0x54,0x44,0x00,0x40,0xFF,
	0x00,0x61,0x83,0x85,0x89,0x71,0x00,0x01,
	0xFE,0xA8,0x82,0xFF,0x00,0x42,0x91,0x99,
	0x66,0x00,0x7E,0x81,0x81,0x7E,0x00,0xFF,
	0x91,0x91,0xFF,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,};


/**
 **  @brief   74HC595芯片（串转并）驱动代码
 **  @param   dat:8位串行数据
 **  @retval  无
 **/
void LED_control(u8 dat){
	u8 i;
	// 将一个字节拆分成串行输入
	for(i=0;i<8;i++){
		SER = dat >> 7; // 先将最高位送入SER中
		dat <<= 1; // 左移1位(去掉最高位)更新数据
		SH = 0; // 给移位寄存器时序脉冲
		_nop_();
		SH = 1; // 检测到上升沿时将SER数据读入移位寄存器中
		_nop_();
	}
	ST = 0; // 当一个字节传输完毕，此时移位寄存器已满。给存储寄存器时序脉冲
	_nop_();
	ST = 1; // 检测到上升沿时将移位寄存器中的8位数据全部读入存储寄存器中。通过并行输出引脚可以直接检测到
	_nop_();
}



/**
 **  @brief   清屏函数
 **  @param   无
 **  @retval  无
 **/
void LED_Matrix_Init(){
	LED_Matrix_PORT = 0xff;
}


/**
 **  @brief   动态显示对应静态画面帧（8*8）
 **  @param   datX：阴极，datY:阳极
 **  @retval  无
 **/
void LED_Animation_Show(u8 datX, u8 datY){
	LED_Matrix_Init(); // 消影
	LED_control(datY); // 阳极码
	LED_Matrix_PORT = ~(0x80>>datX);
}


/**
 **  @brief   控制进入下一帧画面的时间
 **  @param   无
 **  @retval  动画数组索引偏移值
 **/
u16 Next_LED_Index(){
	static u16 count; // count用于记录进入下一帧画面的时间
	static u16 j;    // j为画面帧移动的列数
	
	count++;
	if(count > SPEED){
		count = 0;
		j += COL_NUM;
		if(j > LEN) j = 0;
	}
	return j;
}




/**
 **  @brief   延时法刷新LED点阵
 **  @param   参数说明
 **  @retval  返回值
 **/
void LED_Matrix_Flush_Delay(){
	u8 i; // 当前点亮的列号
	
	// 动态显示一帧画面
	for(i=0;i<8;i++){
		LED_Animation_Show(i, Animation_Array[i + Next_LED_Index()]);
		delay_10us(100);
	}
}


/**
 **  @brief   定时器法刷新LED点阵
 **  @param   参数说明
 **  @retval  返回值
 **/
void LED_Matrix_Flush_Timer(){
	static u8 i;
	
	LED_Animation_Show(i, Animation_Array[i + Next_LED_Index()]);
	if(i >= 8) i = 0;
	else i++;
}


