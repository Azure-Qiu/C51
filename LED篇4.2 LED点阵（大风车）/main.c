#include "LED_Matrix.h"

#define SPEED 8 // 动画速度

u8 code WindMill_Animation_Array[] = {
	0x40,0x63,0x36,0x1C,0x38,0x6C,0xC6,0x02,
	0x0C,0x18,0x90,0xDE,0x7B,0x09,0x18,0x30,
	0x02,0xC6,0x6C,0x38,0x1C,0x36,0x63,0x40,
};


void main(){
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