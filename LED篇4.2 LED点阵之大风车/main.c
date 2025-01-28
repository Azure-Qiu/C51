#include "LED_Matrix.h"
/** 
 **  @brief    LED点阵大风车
 **  @author   QIU
 **  @date     2023.08.23
 **/
/*-------------------------------------------------------------------*/
#define SPEED 8 // 动画速度

// 大风车动画数组
u8 code WindMill_Animation_Array[] = {
	0x40,0x63,0x36,0x1C,0x38,0x6C,0xC6,0x02,
	0x0C,0x18,0x90,0xDE,0x7B,0x09,0x18,0x30,
	0x02,0xC6,0x6C,0x38,0x1C,0x36,0x63,0x40,
};


int main(void){
	// i为当前点亮的LED列号；
	// t为计数器，用于记录进入下一帧画面的时间；
	// step为当前帧数（8的倍数）
	u8 i, t=0, step=0;
	while(1){
		for(i=0;i<8;i++){
			LED_Animation_Show(i, WindMill_Animation_Array[i+step]);
		}
		t++;
		if(t > SPEED){
			t = 0;
			step += 8;
			if(step > sizeof(WindMill_Animation_Array)/sizeof(WindMill_Animation_Array[0]) - 8){
				step = 0;
			}
		}
	}
}