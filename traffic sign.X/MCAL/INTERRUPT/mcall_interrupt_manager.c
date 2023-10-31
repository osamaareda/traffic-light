/* 
 * File:   mcall_interrupt_manager.c
 * Author: osama reda
 *
 * Created on October 8, 2023, 12:14 AM
 */

#include"mcall_interrupt_manager.h"
static volatile uint8 RB4_Flag = 1, RB5_Flag = 1, RB6_Flag = 1, RB7_Flag = 1;
#if INTERRUPT_PRIORITY_LEVELS==ENABLE
void __interrupt() InterruptManagerHigh(void){
    
}

#else
void __interrupt() InterruptManager(void){
    /* ================ TIMER0 Interrupt Start ================= */
    if((INTERRUPT_ENABLE == INTCONbits.T0IE) && (INTERRUPT_OCCUR == INTCONbits.T0IF)){
        TMR0_ISR();
    }
   
}
#endif