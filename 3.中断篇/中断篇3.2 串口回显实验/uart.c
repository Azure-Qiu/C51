#include "uart.h"
/** 
 **  @brief    串口封装函数
 **  @author   QIU
 **  @date     2023.08.23
 **/
/*-------------------------------------------------------------------*/

/**
 **  @brief   串口初始化
 **  @param   波特率（受晶振频率11.0592MHz所限，波特率需小于28800，加倍最大57600）
 **  @retval  无
 **/
void Uart_Init(u16 baud){
	SCON = 0x50;   // 0101 0000（选择串口工作方式为1，且允许串行接收位REN置1）
	TMOD |= 0x20;  // 0010 0000（选定T1定时器，定时器工作方式为8位自动重装）
	PCON = (baud>28800)? 0x80:0x00; // 判断波特率倍频
	TL1 = TH1 = 256 - ((baud>28800)? 57600:28800)/baud;   // 计算初值
	ES = 1; // 打开串口中断标志位
	EA = 1; // 打开总中断标志位
	ET1 = 0; // 禁止定时器T1中断
	TR1 = 1; // 启动定时器T1
}


/**
 **  @brief   串口发送单字节
 **  @param   dat：单字节数据
 **  @retval  返回值
 **/
void Uart_sendByte(u8 dat){
	SBUF = dat; //传入字节
	while(!TI); //等待字节发送完毕
	TI = 0; //清零
}


/**
 **  @brief   串口发送字符串
 **  @param   指向字符串的指针
 **  @retval  无
 **/
void Uart_sendString(u8 *str){
	while(*str != '\0'){
		Uart_sendByte(*str++);
	}
}

// 串口发送小数（6位精度）
void Uart_sendFloat(float f){
	xdata u8 Fdata[15];
	sprintf(Fdata, "%f", f);
	Uart_sendString(Fdata);
}

// 串口发送整数（有符号，可接收四字节）
void Uart_sendInt(long i){
	xdata u8 Idata[15];
	// 按有符号方式输出
	sprintf(Idata, "%ld", i);
	Uart_sendString(Idata);
}


// 串口中断服务函数模板
//void UART_serve() interrupt 4{
//	
//}



