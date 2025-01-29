#include "WS2812.h"
/** 
 **  @brief    WS2812��������@24M��
 **  @author   QIU
 **  @date     2024.04.01
 **/

/*-------------------------------------------------------------------*/

// ���ڴ������WS2812��RGB���ݣ���ά����
xdata u8 WS2812_Array[LED_MAX_NUM][3] = {0};



/**
 **  @brief   Reset�źţ�����50us
 **  @param   ����˵��
 **  @retval  ����ֵ
 **/
void WS2812_Reset(){
	DI = 0;
	delay_10us(5);
}


/**
 **  @brief   ����ָ���Ƶ���ɫ��������ɫ���飩
 **  @param   ����˵��
 **  @retval  ����ֵ
 **/
void WS2812_Set_RGB(u8 num, u8 red, u8 green, u8 blue){ 
	// ����
	WS2812_Array[num-1][0] = red;
	WS2812_Array[num-1][1] = green;
	WS2812_Array[num-1][2] = blue;
}



/**
 **  @brief   ���ָ���Ƶ���ɫ��������ɫ���飩
 **  @param   ����˵��
 **  @retval  ����ֵ
 **/
void WS2812_Clear_RGB(u8 num){ 
	// ���
	memset(WS2812_Array[num-1], 0, sizeof(WS2812_Array[0]));
}



/**
 **  @brief   ����
 **  @param   ��
 **  @retval  ��
 **/
void WS2812_Clear_All(){
	memset(WS2812_Array, 0, sizeof(WS2812_Array));
	WS2812_Update_RGB();
}



/**
 **  @brief   �߼�0��1��ʱ��
 **  @param   ����˵��
 **  @retval  ����ֵ
 **/
void WS2812_Write_0_1(u8 dat){
	if(dat){
		DI = 1; // 800ns��150ns
		_nop_();
		DI = 0; // 450ns��150ns
	}else{
		DI = 1; // 450ns��150ns
		DI = 0; // 800ns��150ns
	}
}


/**
 **  @brief   ���͵����Ƶ�RGBֵ
 **  @param   ����˵��
 **  @retval  ����ֵ
 **/
void WS2812_Send_RGB(u8 *rgb){
	u8 green, red, blue;
	red = rgb[0];
	green = rgb[1];
	blue = rgb[2];
	// ����G
	WS2812_Write_0_1(green & 0x80);WS2812_Write_0_1(green & 0x40);WS2812_Write_0_1(green & 0x20);WS2812_Write_0_1(green & 0x10);
	WS2812_Write_0_1(green & 0x08);WS2812_Write_0_1(green & 0x04);WS2812_Write_0_1(green & 0x02);WS2812_Write_0_1(green & 0x01);
	// ����R
	WS2812_Write_0_1(red & 0x80);WS2812_Write_0_1(red & 0x40);WS2812_Write_0_1(red & 0x20);WS2812_Write_0_1(red & 0x10);
	WS2812_Write_0_1(red & 0x08);WS2812_Write_0_1(red & 0x04);WS2812_Write_0_1(red & 0x02);WS2812_Write_0_1(red & 0x01);
	// ����B
	WS2812_Write_0_1(blue & 0x80);WS2812_Write_0_1(blue & 0x40);WS2812_Write_0_1(blue & 0x20);WS2812_Write_0_1(blue & 0x10);
	WS2812_Write_0_1(blue & 0x08);WS2812_Write_0_1(blue & 0x04);WS2812_Write_0_1(blue & 0x02);WS2812_Write_0_1(blue & 0x01);
}



/**
 **  @brief   �������еƵ�RGBֵ, ����ˢ�¡�
 **  @param   ����˵��
 **  @retval  ����ֵ
 **/
void WS2812_Update_RGB(){
	u8 i;
	// ��λ�ź�
	WS2812_Reset();
	
	for(i=0;i<LED_MAX_NUM;i++){
		WS2812_Send_RGB(WS2812_Array[i]);
	}
}


/**
 **  @brief   ��ˮ�ƣ���һ������
 **  @param   red: ��ɫ��������
 **			  green: ��ɫ��������
 **			  blue: ��ɫ��������
 **			  speed: ������ʱʱ����ms��
 **  @retval  ����ֵ
 **/
void WS2812_Stream_Mode(u8 *red, u8 *green, u8 *blue, u16 speed){
	u8 i;
	for(i=0;i<LED_MAX_NUM;i++){
		WS2812_Set_RGB(i+1, red[i], green[i], blue[i]);
		WS2812_Update_RGB();
		delay_ms(speed);
	}
	WS2812_Clear_All();
}

