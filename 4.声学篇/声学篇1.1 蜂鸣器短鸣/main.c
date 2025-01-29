#include <REGX52.H>
#include <intrins.h>
/** 
 **  @brief    蜂鸣器短鸣
 **  @author   QIU
 **  @date     2023.08.23
 **/
/*-------------------------------------------------------------------*/
#define DELAY_TIME 100 // 持续鸣叫时长

typedef unsigned char u8;
typedef unsigned int u16;

sbit BEEP = P1^5; // 信号端与P1.5引脚相连

void delay_10us(u16 i){
	while(i--);
}

int main(void){
	u8 i = 0;
	while(1){
		while(i < DELAY_TIME){
			// 延时1ms，即周期为2ms，频率为500Hz
			delay_10us(100);
			i++; // 持续DELAY_TIME个周期
			BEEP = !BEEP; // 内部上拉，初始为1，默认占空比为50%
		}
	}
}