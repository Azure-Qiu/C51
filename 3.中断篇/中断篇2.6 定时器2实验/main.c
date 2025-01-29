#include <REGX52.H>
#include <intrins.h>

/*  8052 Extensions  */
//sfr T2CON  = 0xC8;
//sfr T2MOD=0XC9;		//寄存器T2MOD定义
//sfr RCAP2L = 0xCA;
//sfr RCAP2H = 0xCB;
//sfr TL2    = 0xCC;
//sfr TH2    = 0xCD;

main(){
		             //毫秒@11.0592MHz
	T2MOD = 0;		//---- --00  初始化模式寄存器  默认向上计数
	T2CON = 0;		//0000 0000  初始化控制寄存器 一个中断源，16位自动重装模式
	TL2 = 0xff-9;		//设置定时初值  
	TH2 = 0xff;		//设置定时初值
	RCAP2L = 0xff-9;		//设置定时重载值
	RCAP2H = 0xff;		//设置定时重载值
	IE = 0XA0;		//1010 0000 打开全局中断，定时器2中断 ET2 = 1
	TR2 = 1;		//定时器2开始计时
	while(1){
		P2_1=!P2_1;		 //状态取反  3us
		P2_2 =!P2_2;
	}
}


void timer_T2() interrupt 5{	   //中断函数
	TF2=0;				//软件清零定时器2溢出标志位
}
