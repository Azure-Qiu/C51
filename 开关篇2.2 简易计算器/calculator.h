#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

#include "public.h"

// ¼üÖµÃ¶¾Ù
typedef enum{
	KEY_0 = 0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	Dot,
	Addition,
	Subtraction,
	Multiplication,
	Division,
	Calculation
}Key_Value;


extern u8 xdata smg_val[];


void calculator_deal_key(u8, u8);

#endif