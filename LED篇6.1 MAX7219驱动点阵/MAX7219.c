#include "MAX7219.h"
/** 
 **  @brief    MAX7219оƬ��������
 **  @author   QIU
 **  @date     2024.04.14
 **/
/*-------------------------------------------------------------------*/

// ���Ŷ���
sbit DI = P2^0;
sbit CS = P2^1;
sbit CLK = P2^2;

// ָ������
u8 xdata Directives[5][2] = {
	{0x09, 0x00},
	{0x0A, 0x0f},
	{0x0B, 0x07},
	{0x0C, 0x01},
	{0x0F, 0x00},
};

/**
 **  @brief   MAX7219��ʼ��
 **  @param   ��
 **  @retval  ��
 **/
void MAX7219_initial(){
	u8 i, j;
	
	for(i=0;i<5;i++){
		for(j=0;j<MATRIX_NUM;j++){
			MAX7219_write_data(Directives[i][0], Directives[i][1]);
		}
	}

//	MAX7219_write_data(0x09, 0x00); // ���뷽ʽ��������
//	MAX7219_write_data(0x0A, 0x0f); // ���ȵ��ڣ�16��
//	MAX7219_write_data(0x0B, 0x07); // ɨ����ޣ�ɨ��8��
//	MAX7219_write_data(0x0C, 0x01); // �ض�ģʽ��������ʾ
//	MAX7219_write_data(0x0F, 0x00); // ��ʾ���ԣ�������ʾ
}



/**
 **  @brief   д���ֽ�����
 **  @param   16λ����
 **  @retval  ��
 **/
static void MAX7219_write_byte(u8 dat){
	u8 i;	
	for(i=0;i<8;i++){
		// ����ʱ����
		CLK = 0;
		// ȡ��λ
		DI = dat & 0x80;
		// ��λ
		dat <<= 1;
		// ʱ��������
		CLK = 1;
	}
}



/**
 **  @brief   д����
 **  @param   addr: ��ַ
 **  @param	  dat:  ����
 **  @retval  ��
 **/
void MAX7219_write_data(u8 addr, u8 dat){
	// ����Ƭѡ
	CS = 0;
	// �ȷ���ַ
	MAX7219_write_byte(addr);
	// ������
	MAX7219_write_byte(dat);
	// ����Ƭѡ
	CS = 1;
}










