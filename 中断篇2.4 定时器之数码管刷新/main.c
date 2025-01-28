#include "smg.h"
#include "timer.h"
/** 
 **  @brief    数码管定时器刷新
 **  @author   QIU
 **  @date     2024.02.13
 **/
 

/*-------------------------------------------------------------------*/
 
 
u8 dat[] = "LOVE3.14a";
u8 pos = 1;


void main(){
	// 配置定时器0
	TIMERx_init(0, 1843);
	TR0 = 1;
	
	// smg_showChar('f', 1, 0);  // 静态字符显示示例
	
	while(1){
		// smg_showInt(-12345, 1);       // 整数显示示例
		// smg_showString("Iloveyou", 1); // 字符串显示示例
		// smg_showFloat(-3.15678, 3, 1); // 浮点数显示示例
	}
}


// 定时器0的中断服务程序模板
void TIMER0_serve() interrupt 1{
	
	// 重装初值
	TL0 = (65536-2765)%256; //低8位
	TH0 = (65536-2765)/256; //高8位
	
	smg_showString_Bytimer(float2String(-3.1415927, 6), pos);
//	smg_showString_Bytimer(int2String(-6432, true), pos);
//	smg_showString_Bytimer(dat, pos);
}