#include "matrix_key.h"
#include "smg.h"
#include "timer.h"


int main(void){
	TIMERx_init(0, 2000);
	TR0 = 1;
	while(1){
		// ���󰴼�ɨ��
		check_matrixKey_turn();
	}
}


// ��ʱ��0���жϷ������ģ��
void TIMER0_serve() interrupt 1{
	TL0 = (65536-2000)%256; //��8λ
	TH0 = (65536-2000)/256; //��8λ
	
	smg_showString_Bytimer(smg_val, 1);
	
}



