#include "matrix_key.h"
#include "smg.h"

/** 
 **  @brief    实验现象：矩阵按键按下，数码管显示对应数字，同时蜂鸣器作按键提示音
 **  @author   QIU
 **  @date     2023.05.08
 **/

/*-------------------------------------------------------------------*/

int main(void){
	
	smg_showChar(' ', 1, false);
	
	while(1){
		// 反转法
		// check_matrixKey_turn();
		// 扫描法
		check_matrixKey_scan();
	}
}