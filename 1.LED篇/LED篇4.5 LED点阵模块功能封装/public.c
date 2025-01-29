#include "public.h"
/** 
 **  @brief    通用函数
 **  @author   QIU
 **  @data     2023.09.03
 **/

/*-------------------------------------------------------------------*/

/**
 **  @brief   延时函数(10us)
 **  @param   t:0~65535，循环一次约10us
 **  @retval  无
 **/
void delay_10us(u16 t){
	while(t--);
}


/**
 **  @brief   延时函数（ms）
 **  @param   t:0~65535,单位ms
 **  @retval  无
 **/
void delay_ms(u16 t){
	while(t--){
		delay_10us(100);
	}
}


/**
 **  @brief   整数转字符串
 **  @param   num：接受整型值
 **  @param   sign：是否带符号
 **  @retval  返回字符串指针
 **/
u8 * int2String(int num, bit sign){
	static u8 str[8];
	
	// 是否带符号
	if(sign){
		sprintf(str, "%d", num);
	}else{
		sprintf(str, "%u", num);
	}
	// 返回指针
	return str;
}


/**
 **  @brief   浮点数转字符串
 **  @param   num：接受浮点数
 **  @param   len：指定精度，小数点位数0~6（四舍五入）
 **  @retval  返回字符串指针
 **/
u8 * float2String(float num, u8 len){
	static u8 str[10];
	
	// 筛选
	switch(len){
		case 0: sprintf(str, "%.0f", num); break;
		case 1: sprintf(str, "%.1f", num); break;
		case 2: sprintf(str, "%.2f", num); break;
		case 3: sprintf(str, "%.3f", num); break;
		case 4: sprintf(str, "%.4f", num); break;
		case 5: sprintf(str, "%.5f", num); break;
		default: sprintf(str, "%f", num); break;  // 默认6位小数
	}
	// 返回指针
	return str;
}
