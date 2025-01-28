#include <REGX52.H>


typedef unsigned char u8;
typedef unsigned int u16;


void delay(u16 t){
	while(t--);
}


void main(){
	//定义共阴数码管字形码编码
	u8 smg_array[] = {0x3f,0x06,0x5b,0x4f,0x66, //0 1 2 3 4
					 0x6d,0x7d,0x07,0x7f,0x6f}; //5 6 7 8 9 

	while(1){
		int i;
		for(i=0;i<10;i++){
			P0 = smg_array[9-i];
			delay(50000);
		}
		//delay(300000);
		
	}
}