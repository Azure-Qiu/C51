#include <REGX52.H>
/** 
 **  @brief    动态数码管显示I Love You
 **  @author   QIU
 **  @date     2023.08.23
 **/
 /*-------------------------------------------------------------------*/
#define SMG_SELECT_PORT P2 // 位选端口
#define SMG_PORT P0

typedef unsigned char u8;
typedef unsigned int u16;

// 共阴数码管码表(I LOVE YOU)
u8 code smg_array[] = {0x30,0x38,0x3f,0x3e,0x79,0x6e,0x3f,0x3e};

sbit A0 = SMG_SELECT_PORT^2;
sbit A1 = SMG_SELECT_PORT^3;
sbit A2 = SMG_SELECT_PORT^4;		


void delay(u16 t){
	while(t--);
}			
		 
// 位选码，利用十进制取余
void Dec2Bin(u8 i){
	A0 = i % 2;
	i /= 2;
	A1 = i % 2;
	i /= 2;
	A2 = i % 2;
}

int main(void){
	u8 i;
	while(1){
		for(i=0;i<8;i++){
			Dec2Bin(i); // 给38译码器赋值
			SMG_PORT = smg_array[7-i];
			delay(100); // 1ms,实验测试5ms以上能察觉出闪烁
			SMG_PORT  = 0x00; // 消除重影
		}
	}
}