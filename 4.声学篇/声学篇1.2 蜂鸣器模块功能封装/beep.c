#include "beep.h"
/** 
 **  @brief    蜂鸣器功能封装
 **  @author   QIU
 **  @date     2023.08.23
 **/
/*-------------------------------------------------------------------*/

/**
 **  @brief   蜂鸣器单响
 **  @param   t：持续时长
 **  @param   fre：频率HZ
 **  @retval  返回值
 **/
void beep_once(u8 t, u16 fre){
	while(t--){
		BEEP_PORT = !BEEP_PORT; // 取反
		delay_10us(5e4/fre);
	}
}