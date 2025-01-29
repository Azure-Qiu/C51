#include "music.h"
#include "timer.h"

#define MUSIC_SPEED 500

sbit BEEP_PORT = P1^3;

Music_Major_Scale Scale = D_Major_scale;   // D大调

u8 num = 0; // 简谱索引
u8 index;   // 钢琴谱频率索引

u16 music_delay = 100; // 节拍

int main(void){
	TIMERx_init(0, 4608); // 用于控制节拍，5ms
	TIMERx_init(1, 0); // 用于输出不同频率的音阶
	TR0 = 1;

	while(1);
}



// 定时器0的中断服务程序模板
void TIMER0_serve() interrupt 1{
	static u16 counter = 0;
	u8 music_notation;
	
	TL0 = 0; //低8位
	TH0 = 238; //高8位
	
	counter++;
	if(counter == music_delay - 1){
		// 每拍结束暂停5ms
		TR1 = 0;
	}else if(counter >= music_delay){
		counter = 0;
		// 更新乐符
		music_notation = music[num][0]; 
		if(music_notation != 0xff){
			// 更新节拍
			music_delay = MUSIC_SPEED / music[num][1];
			if(music_notation != 0){
				index = Mapping[Scale][music_notation - 1];
				TR1 = 1;
			}
			// 下一个音符
			num++;
		}else{
			// 关闭，全曲终
			TR0 = 0; 
			TR1 = 0;
		}
		
	}
}


// 定时器1的中断服务程序模板
void TIMER1_serve() interrupt 3{
	TL1 = music_Timer_init[index][1]; //低8位
	TH1 = music_Timer_init[index][0]; //高8位
	
	BEEP_PORT = !BEEP_PORT; // 取反
}