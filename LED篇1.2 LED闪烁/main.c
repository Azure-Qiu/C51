#include <REG52.H>
/** 
 **  @brief    LED灯闪烁，大致一秒钟间隔
 **  @author   QIU
 **  @data     2023.08.24
 **/

/*-------------------------------------------------------------------*/
#define LED_PORT P2


// typedef可以将一些复杂的关键字重命名
typedef unsigned char u8; // 0-255，1字节
typedef unsigned int u16; // 0-65535，2字节


int main(void){
	// 声明延时函数
	void delay(u16 msec);
	while(1){
		LED_PORT = 0xfe; // 1111 1110
		delay(50000); // 软件仿真大约450ms
		LED_PORT = 0xff; // 1111 1111
		delay(50000); 
	}
}

// 延时函数 大致10微秒
void delay(u16 msec){
	while(msec--);
}