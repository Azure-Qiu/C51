#ifndef _BEEP_H_
#define _BEEP_H_

#include "public.h"

sbit BEEP_PORT = P1^5;


void beep_once(u8, u16);


#endif