#include <REGX52.H>
#include <INTRINS.H> // 定义了移位函数
/** 
 **  @brief    跑马灯的三种实现方式
 **  @author   QIU
 **  @data     2023.08.24
 **/
 
 /*-------------------------------------------------------------------*/
#define LED_PORT P2
#define DELAY_TIME 20000 // 设置流水灯时间间隔

typedef unsigned char u8;
typedef unsigned int u16;

void delay(u16 sec){
	while(sec--);
}

/*
// 法一：列举法，流水灯一共8种状态。
void ledTest_1(){
	LED_PORT = 0xfe; // 1111 1110
	delay(DELAY_TIME);
	LED_PORT = 0xfd; // 1111 1101
	delay(DELAY_TIME);
	LED_PORT = 0xfb; // 1111 1011
	delay(DELAY_TIME);
	LED_PORT = 0xf7; // 1111 0111
	delay(DELAY_TIME);
	LED_PORT = 0xef; // 1110 1111
	delay(DELAY_TIME);
	LED_PORT = 0xdf; // 1101 1111
	delay(DELAY_TIME);
	LED_PORT = 0xbf; // 1011 1111
	delay(DELAY_TIME);
	LED_PORT  = 0x7f; // 0111 1111
	delay(DELAY_TIME);
}
*/

/*
// 法二：使用左移和取反运算，配合循环实现
void ledTest_2(){
	u8 i;
	for(i=0;i<8;i++){
		LED_PORT = ~(0x01<<i); // 将1左移i位后补0，取反，即第i+1位灯亮
		delay(50000); // 延迟450ms
	}
}
*/

// 法三：使用左移函数_crol_()
void ledTest_3(){
	LED_PORT = _crol_(LED_PORT, 1);  // 左移1位（跟左移运算符不同，高位循环补至低位）
	delay(50000); // 延迟450ms
}


int main(void){
	// 法三：先初始化P2
	LED_PORT = 0xfe;
	delay(50000); // 延迟450ms
	
	while(1){
//		ledTest_1();
//		ledTest_2();
		ledTest_3();
	}
}
