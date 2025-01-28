#ifndef _LED_H_
#define _LED_H_

#include "delay.h"


#define LED_PORT P2


void led_on(u8);
void led_turn(u8);
void led_stream(u16);
void led_run(u16);

#endif
