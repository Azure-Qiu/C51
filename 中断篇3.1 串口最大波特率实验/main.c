#include "public.h"
/** 
 **  @brief    串口最大波特率测试实验
 **  @author   QIU
 **  @date     2024.03.10
 **/
 
 /*-------------------------------------------------------------------*/

/**
 **  @brief   串口初始化
 **  @param   波特率（受晶振频率11.0592MHz所限，波特率需小于28800，加倍最大57600，38400不行）
 **  @retval  无
 **/
void Uart_Init(u16 baud){
	SCON = 0x50;   // 0101 0000（选择串口工作方式为1，且允许串行接收位REN置1）
	TMOD |= 0x20;  // 0010 0000（选定T1定时器，定时器工作方式为8位自动重装）
	PCON = (baud>28800)? 0x80:0x00; // 判断波特率倍频
	TL1 = TH1 = 256 - ((baud>28800)? 57600:28800)/baud;   // 计算初值
	ET1 = 0; // 禁止定时器T1中断
	TR1 = 1; //启动定时器T1
}

/**
 **  @brief   发送单字节数据
 **  @param   单字节数据
 **  @retval  无
 **/
void Uart_SendByte(u8 dat){
	SBUF = dat; // 将字节数据输入至数据缓冲寄存器中
	while(!TI); // 等硬件将TI置1后，即发送成功，退出
	TI = 0; //清零
}

void main(void){
	Uart_Init(57600);
	Uart_SendByte((u8)sizeof(int));
	
	while(1);
}
