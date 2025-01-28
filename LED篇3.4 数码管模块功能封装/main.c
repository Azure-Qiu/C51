#include "smg.h"
/** 
 **  @brief    封装数码管常用功能
 **  @author   QIU
 **  @date     2023.03.10
 **/

/*-------------------------------------------------------------------*/


void main(){
	
	// smg_showChar('f', 1, 0);  // 静态字符显示示例
	
	while(1){
		smg_showInt(-12345, 1);       // 整数显示示例
		// smg_showString("Iloveyou", 1); // 字符串显示示例
		// smg_showFloat(-3.15678, 3, 1); // 浮点数显示示例
	}
}