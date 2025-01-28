#include "calculator.h"
#include "beep.h"
#include "smg.h"
/** 
 **  @brief    计算器相关函数封装
 **  @author   QIU
 **  @date     2024.02.17
 **/
/*-------------------------------------------------------------------*/


// 管理一个用于数码管显示的字符数组，以'\0'结尾
u8 xdata smg_val[10] = {'0', 0};
// 前数值，当前数值
double xdata pre_value = 0, now_value = 0;
// 小数点后位数，整数部分位数
u8 xdata dot_num = 0, pre_dot_num = 0, integer_num = 0, pre_integer_num = 0;
// 存储上一个运算符（默认为加法）
u8 xdata pre_operator_val = Addition;
// 小数点启用标志，新数据输入标志
bit flag_dot = false, flag_new_data = true;
// 矩阵键盘键值数组（4 x 4）
u8 code Matrix_Key_Value[4][4] = {
	{KEY_7, KEY_8, KEY_9, Addition},
	{KEY_4, KEY_5, KEY_6, Subtraction},
	{KEY_1, KEY_2, KEY_3, Multiplication},
	{KEY_0, Dot, Calculation, Division}
};




/**
 **  @brief   根据按键，更新数码管显示值
 **  @param   参数说明
 **  @retval  返回值
 **/
void update_smg_value(u8 row, u8 col){
	// 取出当前键值
	u8 key_val = Matrix_Key_Value[row - 1][col - 1];
	
	switch(key_val){
		// KEY_0，未进入小数部分，且初始为0的状态下，按下无响应
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
			// 每次操作符后首次按键，清空显示字符串
			if(flag_new_data){
				flag_new_data = false;
				// 清空smg_val数组
				memset(smg_val, 0, sizeof(smg_val));
				flag_dot = false;
				// 两数的小数最大个数即为运算结果的小数个数
				pre_dot_num = MAX(pre_dot_num, dot_num);
				pre_integer_num = integer_num;
				dot_num = integer_num = 0;
			}
			         
			if(flag_dot){
				// 已按下小数点时，小数部分
				dot_num++;
				smg_val[integer_num + dot_num] = key_val + '0';		
			}else{
				// 还未按下小数点时，整数部分
				smg_val[integer_num] = key_val + '0';
				integer_num++;
			}
			break;
		case Dot:
			// 如果按下运算符后，直接按小数点无效。
			if(flag_new_data && integer_num != 0) return;
			else flag_new_data = false;
			// 如果未进入小数状态，该键有效
			if(!flag_dot){
				flag_dot = true;
				// 如果初始状态为0
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
			// 只有当输入过新数据或者上个运算符为等号时，运算符键才有效
			if(!flag_new_data || pre_operator_val == Calculation){
				double val;
				int num;
				// 将现有显示的字符串转为数值
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
				// 再更新为当前值
				now_value = atof(smg_val);
			}
			break;
		default:break;
	}
}


// 计算器键值处理
void calculator_deal_key(u8 row, u8 col){
	// 蜂鸣器响应，第三行连接P1.5，不响
	beep_once(50, 2000);
	// 更新数码管的值
	update_smg_value(row, col);
}

