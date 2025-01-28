#ifndef _LED_H_
#define _LED_H_

#include "delay.h"

#define LED_PORT P2

extern u8 flag_led_stream; // 用于控制流水灯何时执行

void led_on(u8);
void led_off(u8);
void led_turn(u8);
void led_stream(u16);
void led_run(u16);
void led_stream_byTimer(void);
void led_run_byTimer(void);

#endif
