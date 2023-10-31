/* 
 * File:   mcal_internal_interrupt.h
 * Author: osama reda
 *
 * Created on October 8, 2023, 12:13 AM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/*-----------------------includes-------------------------*/
#include"mcall_interrupt_cfg.h"

/* ----------------- Macro Functions Declarations -----------------*/
//==========TIMER0 INTERRUPT========//
#if TIMER0_INTERRUPT_FEATURE==ENABLE
/* This routine sets the interrupt enable for the TIMER0 Module */
#define TIMER0_InterruptEnable()          (INTCONbits.TMR0IE = 1)
/* This routine clears the interrupt enable for the TIMER0 Module */
#define TIMER0_InterruptDisable()         (INTCONbits.TMR0IE = 0)
/* This routine clears the interrupt flag for the TIMER0 Module */
#define TIMER0_InterruptFlagClear()       (INTCONbits.TMR0IF = 0)
#if INTERRUPT_PRIORITY_LEVELS==ENABLE 
/* This routine set the TIMER0 Module Interrupt Priority to be High priority */
#define TIMER0_HighPrioritySet()          (INTCON2bits.TMR0IP = 1)
/* This routine set the TIMER0 Module Interrupt Priority to be Low priority */
#define TIMER0_LowPrioritySet()           (INTCON2bits.TMR0IP = 0)
#endif
#endif


#endif	/* MCAL_INTERNAL_INTERRUPT_H */