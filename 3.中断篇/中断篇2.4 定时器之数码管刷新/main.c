#include "smg.h"
#include "timer.h"
/** 
 **  @brief    ����ܶ�ʱ��ˢ��
 **  @author   QIU
 **  @date     2024.02.13
 **/
 

/*-------------------------------------------------------------------*/
 
 
u8 dat[] = "LOVE3.14a";
u8 pos = 1;


void main(){
	// ���ö�ʱ��0
	TIMERx_init(0, 1843);
	TR0 = 1;
	
	// smg_showChar('f', 1, 0);  // ��̬�ַ���ʾʾ��
	
	while(1){
		// smg_showInt(-12345, 1);       // ������ʾʾ��
		// smg_showString("Iloveyou", 1); // �ַ�����ʾʾ��
		// smg_showFloat(-3.15678, 3, 1); // ��������ʾʾ��
	}
}


// ��ʱ��0���жϷ������ģ��
void TIMER0_serve() interrupt 1{
	
	// ��װ��ֵ
	TL0 = (65536-2765)%256; //��8λ
	TH0 = (65536-2765)/256; //��8λ
	
	smg_showString_Bytimer(float2String(-3.1415927, 6), pos);
//	smg_showString_Bytimer(int2String(-6432, true), pos);
//	smg_showString_Bytimer(dat, pos);
}