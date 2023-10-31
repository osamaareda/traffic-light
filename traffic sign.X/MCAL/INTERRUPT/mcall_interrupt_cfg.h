/* 
 * File:   mcall_interrupt_cfg.h
 * Author: osama reda
 *
 * Created on October 8, 2023, 12:16 AM
 */

#ifndef MCALL_INTERRUPT_CFG_H
#define	MCALL_INTERRUPT_CFG_H

/*-----------------------includes-------------------------*/
#include"../mcal_std_types.h"
#include"mcal_interrupt_gen_cfg.h"
#include"../GPIO/gpio.h"
/*----------------macros declaration-----------------*/
#define INTERRUPT_ENABLE       1
#define INTERRUPT_DISABLE      1
#define INTERRUPT_OCCUR        1
#define INTERRUPT_NOT_OCCUR    1
#define INTERRUPT_PRIORITY_ENABLE    1
#define INTERRUPT_PRIORITY_DISABLE   0

/* ----------------- Macro Functions Declarations -----------------*/
#if INTERRUPT_PRIORITY_LEVELS==ENABLE
//This macro will enable priority levels on interrupts. 
#define INTERRUPT_PriorityLevelsEnable()         (RCONbits.IPEN=1)
//This macro will disable  priority levels on interrupts.
#define INTERRUPT_PriorityLevelsDisable()        (RCONbits.IPEN=0)

//This macro will enable high priority global interrupts. 
#define INTERRUPT_GlobalInterruptHighEnable()    (INTCONbits.GIEH=1)
//This macro will disable high priority global interrupts. 
#define INTERRUPT_GlobalInterruptHighDisable()   (INTCONbits.GIEH=0)

//This macro will enable low priority global interrupts.
#define INTERRUPT_GlobalInterruptLowEnable()     (INTCONbits.GIEL=1)   
//This macro will disable low priority global interrupts.
#define INTERRUPT_GlobalInterruptLowDisable()    (INTCONbits.GIEL=0) 
#elif INTERRUPT_PRIORITY_LEVELS==DISABLE
//This macro will enable global interrupts.
#define INTERRUPT_GlobalInterruptEnable()        (INTCONbits.GIE=1)  
//This macro will disable global interrupts.
#define INTERRUPT_GlobalInterruptDisable()       (INTCONbits.GIE=0)   
//This macro will enable peripheral interrupts.
#define INTERRUPT_PeripheralInterruptEnable()    (INTCONbits.PEIE=1)
//This macro will disable peripheral interrupts.
#define INTERRUPT_PeripheralInterruptDisable()   (INTCONbits.PEIE=0)
#endif

/*---------------data type declaration---------------*/
typedef enum{
   LOW_PRIORITY,
   HIGH_PRIORITY        
}interrupt_priority_t;
#endif	/* MCALL_INTERRUPT_CFG_H */