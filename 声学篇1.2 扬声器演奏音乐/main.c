#include "music.h"
#include "timer.h"

#define MUSIC_SPEED 500

sbit BEEP_PORT = P1^3;

Music_Major_Scale Scale = D_Major_scale;   // D���

u8 num = 0; // ��������
u8 index;   // ������Ƶ������

u16 music_delay = 100; // ����

int main(void){
	TIMERx_init(0, 4608); // ���ڿ��ƽ��ģ�5ms
	TIMERx_init(1, 0); // ���������ͬƵ�ʵ�����
	TR0 = 1;

	while(1);
}



// ��ʱ��0���жϷ������ģ��
void TIMER0_serve() interrupt 1{
	static u16 counter = 0;
	u8 music_notation;
	
	TL0 = 0; //��8λ
	TH0 = 238; //��8λ
	
	counter++;
	if(counter == music_delay - 1){
		// ÿ�Ľ�����ͣ5ms
		TR1 = 0;
	}else if(counter >= music_delay){
		counter = 0;
		// �����ַ�
		music_notation = music[num][0]; 
		if(music_notation != 0xff){
			// ���½���
			music_delay = MUSIC_SPEED / music[num][1];
			if(music_notation != 0){
				index = Mapping[Scale][music_notation - 1];
				TR1 = 1;
			}
			// ��һ������
			num++;
		}else{
			// �رգ�ȫ����
			TR0 = 0; 
			TR1 = 0;
		}
		
	}
}


// ��ʱ��1���жϷ������ģ��
void TIMER1_serve() interrupt 3{
	TL1 = music_Timer_init[index][1]; //��8λ
	TH1 = music_Timer_init[index][0]; //��8λ
	
	BEEP_PORT = !BEEP_PORT; // ȡ��
}