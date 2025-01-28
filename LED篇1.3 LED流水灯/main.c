#include <REGX52.H>
/** 
 **  @brief    LED流水灯实验
 **  @author   QIU
 **  @data     2023.08.24
 **/

/*-------------------------------------------------------------------*/
#define LED_PORT P2

typedef unsigned char u8;
typedef unsigned int u16;

void delay(u16 t){
	while(t--);
}

void main(){
	
	while(1){
		u8 i;
		LED_PORT = 0xfe; //1111 1110
		delay(50000);
		for(i=0;i<8;i++){
			LED_PORT <<= 1; //左移一位
			delay(50000); //延时450ms
		}
	}
}