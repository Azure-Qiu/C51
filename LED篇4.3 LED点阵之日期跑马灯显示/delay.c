#include "delay.h"
/** 
 **  @brief    ͨ�ú���
 **  @author   QIU
 **  @data     2023.08.23
 **/

/*-------------------------------------------------------------------*/

/**
 **  @brief   ��ʱ����(10us)
 **  @param   t:0~65535��ѭ��һ��Լ10us
 **  @retval  ��
 **/
void delay_10us(u16 t){
	while(t--);
}


/**
 **  @brief   ��ʱ������ms��
 **  @param   t:0~65535,��λms
 **  @retval  ��
 **/
void delay_ms(u16 t){
	while(t--){
		delay_10us(100);
	}
}

