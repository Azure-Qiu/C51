#include "REGX52.H"
/** 
 **  @brief    静态数码管显示字符
 **  @author   QIU
 **  @date     2023.08.23
 **/
 
/*-------------------------------------------------------------------*/
#define SMG_PORT P0

// 重定义数据类型
typedef unsigned char u8;
typedef unsigned int u16;

// 共阴极数码管字形码编码
u8 code smgduan[] = {0x3f,0x06,0x5b,0x4f,0x66, // 0 1 2 3 4
					 0x6d,0x7d,0x07,0x7f,0x6f, // 5 6 7 8 9
					 0x77,0x7c,0x58,0x5e,0x79, // A b c d E
					 0x71,0x76,0x30,0x0e,0x38, // F H I J L
					 0x54,0x5c,0x73,0x67,0x50, // n o p q r
					 0x6d,0x3e,0x1c,0x6e};     // s U v y  

int main(void){
	// P0口控制数码管显示字符
	SMG_PORT = smgduan[14]; // E
	while(1);
}
