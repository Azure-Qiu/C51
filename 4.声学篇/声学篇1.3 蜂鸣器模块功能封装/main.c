#include "beep.h"


void main(){
	// 以1000Hz频率，50%占空比，持续时间约1s
	beep_once(100, 1000);
	while(1);
}