/* 
 * File:   mcal_external_interrupt.h
 * Author: osama reda
 *
 * Created on October 8, 2023, 12:13 AM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/*-----------------------includes-------------------------*/
#include"mcall_interrupt_cfg.h"

/*----------------macros declaration-----------------*/


/* ----------------- Macro Functions Declarations -----------------*/
#if EXTERNAL_INTERRUPT_INTx_FEATURE==ENABLE
//enable the external interrupt, INT0 
#define EXT_INT0_InterruptEnable()        (INTCONbits.INT0E=1)
//disable the external interrupt, INT0
#define EXT_INT0_InterruptDisable()       (INTCONbits.INT0E=0)       
   
//clears the interrupt flag for the external interrupt, INT0 
#define EXT_INT0_InterruptFlagClear()     (INTCONbits.INT0F=0)
//set the edge detect of the INT0 to positive edge 
#define EXT_INT0_RisingEdgeSet()          (INTCON2bits.INTEDG0=1)
//set the edge detect of the INT0 to negative edge 
#define EXT_INT0_FallingEdgeSet()         (INTCON2bits.INTEDG0=0)

//enable the external interrupt, INT1
#define EXT_INT1_InterruptEnable()        (INTCON3bits.INT1E=1)  
//disable the external interrupt, INT1
#define EXT_INT1_InterruptDisable()       (INTCON3bits.INT1E=0)       
   
//clears the interrupt flag for the external interrupt, INT1 
#define EXT_INT1_InterruptFlagClear()     (INTCON3bits.INT1F=0)
//set the edge detect of the INT1 to positive edge 
#define EXT_INT1_RisingEdgeSet()          (INTCON2bits.INTEDG1=1)
//set the edge detect of the INT1 to negative edge 
#define EXT_INT1_FallingEdgeSet()         (INTCON2bits.INTEDG1=0)

//enable the external interrupt, INT2
#define EXT_INT2_InterruptEnable()        (INTCON3bits.INT2E=1)  
//disable the external interrupt, INT2
#define EXT_INT2_InterruptDisable()       (INTCON3bits.INT2E=0)       
   
//clears the interrupt flag for the external interrupt, INT
#define EXT_INT2_InterruptFlagClear()     (INTCON3bits.INT2F=0)
//set the edge detect of the INT2 to positive edge 
#define EXT_INT2_RisingEdgeSet()          (INTCON2bits.INTEDG2=1)
//set the edge detect of the INT2 to negative edge 
#define EXT_INT2_FallingEdgeSet()         (INTCON2bits.INTEDG2=0)

#if INTERRUPT_PRIORITY_LEVELS==ENABLE
//set the INT1 Priority to be High  
#define EXT_INT1_HighPrioritySet()        (INTCON3bits.INT1P=1)
//set the INT1 Priority to be low
#define EXT_INT1_LowPrioritySet()         (INTCON3bits.INT1P=0)
//set the INT2 Priority to be High  
#define EXT_INT2_HighPrioritySet()        (INTCON3bits.INT2P=1)
//set the INT2 Priority to be low
#define EXT_INT2_LowPrioritySet()         (INTCON3bits.INT2P=0)
#endif

#endif

#if EXTERNAL_INTERRUPT_OnChange_FEATURE==ENABLE
//disable for the external interrupt, RBx 
#define EXT_RBx_InterruptEnable()         (INTCONbits.RBIE=1)
//enable for the external interrupt, RBx 
#define EXT_RBx_InterruptDisable()        (INTCONbits.RBIE=0)
//clears the interrupt flag for the external interrupt, RBx 
#define EXT_RBx_InterruptFlagClear()      (INTCONbits.RBIF=0)

#if INTERRUPT_PRIORITY_LEVELS==ENABLE 
//set the RBx Priority to be High  
#define EXT_RBx_Priority_High()           (INTCON2bits.RBIP=1)
//set the RBx External to be Low  
#define EXT_RBx_Priority_Low()            (INTCON2bits.RBIP=0)
#endif

#endif

/*---------------data type declaration---------------*/
typedef enum{
    FALLING_EDGE,
    RISING_EDGE
}interrupt_INTx_edge;

typedef enum{
    _INT0,
    _INT1,
    _INT2       
}interrupt_INTx_src;

typedef struct{
    void (* EXT_InterruptHandler)(void);
    pin_config_t INTx_pin;
    interrupt_INTx_edge edge;
    interrupt_INTx_src source;
    interrupt_priority_t priority;
}interrupt_INTx_t;

typedef struct{
    void (* EXT_InterruptHandler_HIGH)(void);
    void (* EXT_InterruptHandler_LOW)(void);
    pin_config_t RBx_pin;
    interrupt_priority_t priority;
}interrupt_RBx_t;

/*----------------function declaration-----------------*/
Std_ReturnType interrupt_INTx_init(interrupt_INTx_t *_interrupt);
Std_ReturnType interrupt_INTx_deInit(interrupt_INTx_t *_interrupt);
Std_ReturnType interrupt_RBx_init(interrupt_RBx_t *_interrupt);
Std_ReturnType interrupt_RBx_deInit(interrupt_RBx_t *_interrupt);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */