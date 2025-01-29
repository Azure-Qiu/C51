#include "interrupt.h"
/** 
 **  @brief    开关实验（将开关接至P3_2引脚，通过外部中断INT0，可以检测开关信号，并点亮led0提示）
 **  @author   QIU
 **  @date     2024.04.06
 **/
/*-------------------------------------------------------------------*/

sbit LED_Port = P2^0;


int main(void){
	// 初始化INT0
	INTx_init(0);
	while(1);
}

// 外部中断0的中断服务程序模板
void INT1_serve() interrupt 0{
	LED_Port = 0;
}