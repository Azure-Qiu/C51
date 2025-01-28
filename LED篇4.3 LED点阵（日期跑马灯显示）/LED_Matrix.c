#include "LED_Matrix.h"


#define LED_PORT P0


sbit SER = P3^4; //��������
sbit ST = P3^5; //�洢�Ĵ���ʱ������
sbit SH = P3^6; //��λ�洢��ʱ������

/**
  *  @brief ��ת����������
  *  @param dat:8λ��������
  *  @retval ����ֵ����
  */
void LED_control(u8 dat){
	u8 i;
	//��һ���ֽڲ�ֳɴ�������
	for(i=0;i<8;i++){
		SER = dat >> 7; //�Ƚ����λ����SER��
		dat <<= 1; //����1λ(ȥ�����λ)��������
		SH = 0; //����λ�Ĵ���ʱ������
		delay_10us(1);
		SH = 1; //��⵽������ʱ��SER���ݶ�����λ�Ĵ�����
		delay_10us(1);
	}
	ST = 0; //��һ���ֽڴ�����ϣ���ʱ��λ�Ĵ������������洢�Ĵ���ʱ������
	delay_10us(1);
	ST = 1;//��⵽������ʱ����λ�Ĵ����е�8λ����ȫ������洢�Ĵ����С�ͨ������������ſ���ֱ�Ӽ�⵽
	delay_10us(1);
}


void LED_Init(){
	LED_PORT = 0xff;
}



/**
  *  @brief ��ʾ��Ӧ��̬���棨8*8��
  *  @param datX��������datY:����
  *  @retval
  */
void LED_Animation_Show(u8 datX, u8 datY){
	LED_control(datY); //������
	LED_PORT = ~(0x80>>datX);
	delay_10us(100);
	LED_Init(); //��Ӱ
}
