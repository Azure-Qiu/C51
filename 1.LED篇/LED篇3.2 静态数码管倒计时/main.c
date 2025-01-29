#include <REGX52.H>
/** 
 **  @brief    静态数码管实现倒计时
 **  @author   QIU
 **  @date     2023.08.23
 **/
 
/*-------------------------------------------------------------------*/
#define SMG_PORT P0

typedef unsigned char u8;
typedef unsigned int u16;


void delay(u16 t){
	while(t--);
}


int main(void){
	// 定义共阴数码管字形码编码
	u8 code smg_array[] = {0x3f,0x06,0x5b,0x4f,0x66,  // 0 1 2 3 4
					       0x6d,0x7d,0x07,0x7f,0x6f}; // 5 6 7 8 9 

	while(1){
		int i;
		for(i=0;i<10;i++){
			SMG_PORT = smg_array[9-i];
			delay(50000);
		}
		delay(60000);
	}
}