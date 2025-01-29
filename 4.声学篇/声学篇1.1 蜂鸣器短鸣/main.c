#include <REG52.H>

#define DELAY_TIME 100

typedef unsigned char u8;
typedef unsigned int u16;

sbit BEEP = P1^5; //信号端与P1.5引脚相连

void delay(u16 i){
	while(i--);
}

void main(){
	u8 i = 0;
	while(1){
		while(i < DELAY_TIME){
			BEEP = !BEEP; //内部上拉，初始为1，占空比为50%
			delay(100); //延时10ms，即频率为50Hz
			i++;
		}
	}
	
}