#include "LED_Matrix.h"
/** 
 **  @brief    KED点阵之滚动字幕
 **  @author   QIU
 **  @date     2023.08.23
 **/
/*-------------------------------------------------------------------*/
#define SPEED 50

// 2022年12月30日
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


int main(void){
	// i为当前点亮的LED列号；
	// count为计数器，用于记录进入下一帧画面的时间；
	// j为当前帧数（偏移量）
	u8 i, count=0, j=0;
	LED_Init();
	while(1){
		for(i=0;i<8;i++){
			LED_Animation_Show(i, Animation_Array[i+j]);
		}
		count++;
		if(count > SPEED){
			count = 0;
			j++; // 移动一列
			if(j > sizeof(Animation_Array)/sizeof(Animation_Array[0]) - 8){
				j = 0;
			}
		}
	}
}


	
	
