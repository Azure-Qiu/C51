#include "interrupt.h"
/** 
 **  @brief    外部中断封装
 **  @author   QIU
 **  @data     2023.08.31
 **/

/*-------------------------------------------------------------------*/


/**
 **  @brief   配置外部中断x
 **  @param   x：对应外部中断编号
 **  @retval  无
 **/
void INTx_init(u8 x){
	switch(x){
		case 0:
			IT0 = 1; // 设置外部中断0触发方式，下降沿触发
			EX0 = 1; // 使能外部中断0
			break;
		case 1:
			IT1 = 1; // 设置外部中断1触发方式，下降沿触发
			EX1 = 1; // 使能外部中断1
			break;
	}
	EA = 1;  // 使能总中断
}



// 外部中断0的中断服务程序模板
//void INT1_serve() interrupt 0{
//	;
//}


// 外部中断1的中断服务程序模板
//void INT1_serve() interrupt 2{
//	;
//}



