#include "matrix_key.h"
#include "smg.h"
#include "timer.h"

int main(void){
	TIMERx_init(0, 1843); // 2ms
	TR0 = 1;
	
	while(1){
		check_matrixKey_turn();
//		check_matrixKey_scan();
	}
}


// ��ʱ��0���жϷ������ģ��
void TIMER0_serve() interrupt 1{
	TL0 = (65536-1843)%256; //��8λ
	TH0 = (65536-1843)/256; //��8λ
	
//	check_matrixKey_turn_ByTimer();
//	check_matrixKey_scan_ByTimer();
	smg_showString_Bytimer(int2String(key_val, true), 1);
	
}


