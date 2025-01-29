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


// 定时器0的中断服务程序模板
void TIMER0_serve() interrupt 1{
	TL0 = (65536-1843)%256; //低8位
	TH0 = (65536-1843)/256; //高8位
	
//	check_matrixKey_turn_ByTimer();
//	check_matrixKey_scan_ByTimer();
	smg_showString_Bytimer(int2String(key_val, true), 1);
	
}


