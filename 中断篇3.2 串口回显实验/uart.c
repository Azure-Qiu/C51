#include "uart.h"
/** 
 **  @brief    ���ڷ�װ����
 **  @author   QIU
 **  @date     2023.08.23
 **/
/*-------------------------------------------------------------------*/

/**
 **  @brief   ���ڳ�ʼ��
 **  @param   �����ʣ��ܾ���Ƶ��11.0592MHz���ޣ���������С��28800���ӱ����57600��
 **  @retval  ��
 **/
void Uart_Init(u16 baud){
	SCON = 0x50;   // 0101 0000��ѡ�񴮿ڹ�����ʽΪ1���������н���λREN��1��
	TMOD |= 0x20;  // 0010 0000��ѡ��T1��ʱ������ʱ��������ʽΪ8λ�Զ���װ��
	PCON = (baud>28800)? 0x80:0x00; // �жϲ����ʱ�Ƶ
	TL1 = TH1 = 256 - ((baud>28800)? 57600:28800)/baud;   // �����ֵ
	ES = 1; // �򿪴����жϱ�־λ
	EA = 1; // �����жϱ�־λ
	ET1 = 0; // ��ֹ��ʱ��T1�ж�
	TR1 = 1; // ������ʱ��T1
}


/**
 **  @brief   ���ڷ��͵��ֽ�
 **  @param   dat�����ֽ�����
 **  @retval  ����ֵ
 **/
void Uart_sendByte(u8 dat){
	SBUF = dat; //�����ֽ�
	while(!TI); //�ȴ��ֽڷ������
	TI = 0; //����
}


/**
 **  @brief   ���ڷ����ַ���
 **  @param   ָ���ַ�����ָ��
 **  @retval  ��
 **/
void Uart_sendString(u8 *str){
	while(*str != '\0'){
		Uart_sendByte(*str++);
	}
}

// ���ڷ���С����6λ���ȣ�
void Uart_sendFloat(float f){
	xdata u8 Fdata[15];
	sprintf(Fdata, "%f", f);
	Uart_sendString(Fdata);
}

// ���ڷ����������з��ţ��ɽ������ֽڣ�
void Uart_sendInt(long i){
	xdata u8 Idata[15];
	// ���з��ŷ�ʽ���
	sprintf(Idata, "%ld", i);
	Uart_sendString(Idata);
}


// �����жϷ�����ģ��
//void UART_serve() interrupt 4{
//	
//}



