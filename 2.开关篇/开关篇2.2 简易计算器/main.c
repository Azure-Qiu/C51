#include "matrix_key.h"
#include "smg.h"
#include "timer.h"


int main(void){
	TIMERx_init(0, 2000);
	TR0 = 1;
	while(1){
		// 矩阵按键扫描
		check_matrixKey_turn();
	}
}


// 定时器0的中断服务程序模板
void TIMER0_serve() interrupt 1{
	TL0 = (65536-2000)%256; //低8位
	TH0 = (65536-2000)/256; //高8位
	
	smg_showString_Bytimer(smg_val, 1);
	
}



