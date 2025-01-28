#include <REGX52.H>
#define LED_PORT P0

typedef unsigned char u8;
typedef unsigned int u16;

sbit SER = P3^4; //串行输入
sbit ST = P3^5; //存储寄存器时钟引脚
sbit SH = P3^6; //移位存储器时钟引脚

u8 code LED_portX_Array[] = {0x7e,0xbd,0xdb,0xe7};
u8 code LED_portY_Array[] = {0x38,0x7c,0x7e,0x3f};


void delay(u16 t){
	while(t--);
}

void LED_control(u8 dat){
	u8 i;
	//将一个字节拆分成串行输入
	for(i=0;i<8;i++){
		SER = dat >> 7; //先将最高位送入SER中
		dat <<= 1; //左移1位(去掉最高位)更新数据
		SH = 0; //给移位寄存器时序脉冲
		delay(1);
		SH = 1; //检测到上升沿时将SER数据读入移位寄存器中
		delay(1);
	}
	ST = 0; //当一个字节传输完毕，此时移位寄存器已满。给存储寄存器时序脉冲
	delay(1);
	ST = 1;//检测到上升沿时将移位寄存器中的8位数据全部读入存储寄存器中。通过并行输出引脚可以直接检测到
	delay(1);
}




void main(){
	u8 i; //必须先定义，放在第一个
	P0 = 0xff; //初始全熄灭
	while(1){
		for(i=0;i<4;i++){
			LED_control(0x00);
			LED_control(LED_portY_Array[i]);
			P0 = LED_portX_Array[i];
			delay(100); //1ms
			
		}
	}
}