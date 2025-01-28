#include "beep.h"

/**
   *  @brief 蜂鸣器单响
   *  @param t 持续时长, fre 频率HZ
   *  @retval
   */
void beep_once(u8 t, u16 fre){
	while(t--){
		BEEP_PORT = !BEEP_PORT; // 取反
		delay_10us(1e5/2/fre);
	}
}