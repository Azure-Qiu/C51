#ifndef _MAX7219_H_
#define _MAX7219_H_


#include "public.h"

#define MATRIX_NUM 2


void MAX7219_initial();
void MAX7219_write_data(u8 addr, u8 dat);

#endif