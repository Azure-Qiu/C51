#include <REGX52.H>

typedef unsigned char u8;
typedef unsigned int u16;

void delay(u16 t){
	while(t--);
}


//共阴数码管码表(I LOVE YOU)
u8 code smg_array[] = {0x30,0x38,0x3f,0x3e,0x79,0x6e,0x3f,0x3e};

sbit A0 = P2^2;
sbit A1 = P2^3;
sbit A2 = P2^4;		
					 
//位选码，利用十进制取余
void Dec2Bin(u8 i){
	A0 = i % 2;
	i /= 2;
	A1 = i % 2;
	i /= 2;
	A2 = i % 2;
}


void main(){
	u8 i;
	while(1){
		for(i=0;i<8;i++){
			Dec2Bin(i);
			P0 = smg_array[7-i];
			delay(100); //1ms,实验测试5ms以上能察觉出闪烁
			P0 = 0x00; //消除重影
		}
	}
}