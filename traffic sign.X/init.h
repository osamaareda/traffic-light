/* 
 * File:   init.h
 * Author: osama reda
 *
 * Created on October 31, 2023, 4:11 AM
 */

#ifndef INIT_H
#define	INIT_H

/*-------------------includes---------------------*/
#include "ECUAL/LED/led.h"
#include "ECUAL/7_SEGMENT/seven_segment.h"
#include "ECUAL/LCD/lcd.h"
#include "MCAL/INTERRUPT/mcal_external_interrupt.h"
#include "MCAL/TIMER0/timer0.h"

/*--------------function declaration--------------*/
void init(void);
void MY_TMR0_ISR(void);
/*-----------------------------------------*/
extern led_config_t led_red;
extern led_config_t led_yellow;
extern led_config_t led_green;
extern timer0_config_t timer0;
extern seven_segment_config_t seg_red1;
extern seven_segment_config_t seg_green1;
extern seven_segment_config_t seg_red2;
extern seven_segment_config_t seg_green2;
#endif	/* INIT_H */

