#include "calculator.h"
#include "beep.h"
#include "smg.h"
/** 
 **  @brief    ��������غ�����װ
 **  @author   QIU
 **  @date     2024.02.17
 **/
/*-------------------------------------------------------------------*/


// ����һ�������������ʾ���ַ����飬��'\0'��β
u8 xdata smg_val[10] = {'0', 0};
// ǰ��ֵ����ǰ��ֵ
double xdata pre_value = 0, now_value = 0;
// С�����λ������������λ��
u8 xdata dot_num = 0, pre_dot_num = 0, integer_num = 0, pre_integer_num = 0;
// �洢��һ���������Ĭ��Ϊ�ӷ���
u8 xdata pre_operator_val = Addition;
// С�������ñ�־�������������־
bit flag_dot = false, flag_new_data = true;
// ������̼�ֵ���飨4 x 4��
u8 code Matrix_Key_Value[4][4] = {
	{KEY_7, KEY_8, KEY_9, Addition},
	{KEY_4, KEY_5, KEY_6, Subtraction},
	{KEY_1, KEY_2, KEY_3, Multiplication},
	{KEY_0, Dot, Calculation, Division}
};




/**
 **  @brief   ���ݰ����������������ʾֵ
 **  @param   ����˵��
 **  @retval  ����ֵ
 **/
void update_smg_value(u8 row, u8 col){
	// ȡ����ǰ��ֵ
	u8 key_val = Matrix_Key_Value[row - 1][col - 1];
	
	switch(key_val){
		// KEY_0��δ����С�����֣��ҳ�ʼΪ0��״̬�£���������Ӧ
		case KEY_0: if(!flag_dot && integer_num == 0 && smg_val[0] == '0') return;
		case KEY_1:
		case KEY_2:	
		case KEY_3:
		case KEY_4:	
		case KEY_5:
		case KEY_6:	
		case KEY_7:
		case KEY_8:	
		case KEY_9:	
			// ÿ�β��������״ΰ����������ʾ�ַ���
			if(flag_new_data){
				flag_new_data = false;
				// ���smg_val����
				memset(smg_val, 0, sizeof(smg_val));
				flag_dot = false;
				// ������С����������Ϊ��������С������
				pre_dot_num = MAX(pre_dot_num, dot_num);
				pre_integer_num = integer_num;
				dot_num = integer_num = 0;
			}
			         
			if(flag_dot){
				// �Ѱ���С����ʱ��С������
				dot_num++;
				smg_val[integer_num + dot_num] = key_val + '0';		
			}else{
				// ��δ����С����ʱ����������
				smg_val[integer_num] = key_val + '0';
				integer_num++;
			}
			break;
		case Dot:
			// ��������������ֱ�Ӱ�С������Ч��
			if(flag_new_data && integer_num != 0) return;
			else flag_new_data = false;
			// ���δ����С��״̬���ü���Ч
			if(!flag_dot){
				flag_dot = true;
				// �����ʼ״̬Ϊ0
				if(integer_num == 0 && smg_val[0] == '0'){
					integer_num++;
					smg_val[integer_num] = '.';
				}else{
					smg_val[integer_num] = '.';
				}
			}
			break;
		case Addition:
		case Subtraction:
		case Multiplication:
		case Division:
		case Calculation:
			// ֻ�е�����������ݻ����ϸ������Ϊ�Ⱥ�ʱ�������������Ч
			if(!flag_new_data || pre_operator_val == Calculation){
				double val;
				int num;
				// ��������ʾ���ַ���תΪ��ֵ
				pre_value = now_value;
				now_value = atof(smg_val);
				switch(pre_operator_val){
					case Addition: val = pre_value + now_value; num = MAX(pre_dot_num, dot_num); break;
					case Subtraction: val = pre_value - now_value; num = MAX(pre_dot_num, dot_num); break;
					case Multiplication: val = pre_value * now_value; num = pre_dot_num + dot_num; break;
					case Division: val = pre_value / now_value; num = 6; break;
					case Calculation: val = now_value; num = MAX(pre_dot_num, dot_num); break;
				}
				sprintf(smg_val, "%.*f", num, val); 
				pre_operator_val = key_val; 
				flag_new_data = true;
				// �ٸ���Ϊ��ǰֵ
				now_value = atof(smg_val);
			}
			break;
		default:break;
	}
}


// ��������ֵ����
void calculator_deal_key(u8 row, u8 col){
	// ��������Ӧ������������P1.5������
	beep_once(50, 2000);
	// ��������ܵ�ֵ
	update_smg_value(row, col);
}

