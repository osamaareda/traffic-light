/* 
 * File:   timer0.c
 * Author: osama reda
 *
 * Created on October 29, 2023, 4:48 PM
 */

#include"timer0.h"

/* Pointer to function to hold the callbacks func for TIMER0 */

#if TIMER0_INTERRUPT_FEATURE==ENABLE
    static void (*TMR0_InterruptHandler)(void) = NULL;
#endif
static uint16 timer0_preload = 0;

/* helper function to initialize ADC interrupt */
static inline void Timer0_Prescaler_Config(const timer0_config_t *_timer);
static inline void Timer0_Mode_Select(const timer0_config_t *_timer);
static inline void Timer0_Register_Size_Config(const timer0_config_t *_timer);

/**
 * @brief :Initializes TIMER0
 * @Description :This routine initializes TIMER0.
 *               This routine must be called before any other TIMER0 routine is called.
 *               This routine should only be called once during system initialization.
 * @param : _timer -> pointer to (timer0_config_t) TIMER0 configurations structure @ref timer0_config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if TIMER0_CONFIG==ENABLE
Std_ReturnType Timer0_Init(const timer0_config_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the TIMER0 */
        TIMER0_MODULE_DISABLE();
        /* Configure the Prescaler for TIMER0 */
        Timer0_Prescaler_Config(_timer);
         /* select the mode for TIMER0 */
        Timer0_Mode_Select(_timer);
        /* Configure register size 8 or 16 bits */
        Timer0_Register_Size_Config(_timer);
        /*set preload value */
        TMR0H = (_timer->timer0_preload_value) >> 8;
        TMR0L = (uint8)(_timer->timer0_preload_value);
        timer0_preload = _timer->timer0_preload_value;
        /* Configure the interrupt  */        
        #if TIMER0_INTERRUPT_FEATURE==ENABLE
        TIMER0_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS==ENABLE 
        INTERRUPT_PriorityLevelsEnable();
        if(HIGH_PRIORITY == _timer->priority){
            /* Enables all high-priority interrupts */
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER0_HighPrioritySet();
        }
        else if(LOW_PRIORITY == _timer->priority){
            /* Enables all unmasked peripheral interrupts */
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER0_LowPrioritySet();
        }
        #elif INTERRUPT_PRIORITY_LEVELS==DISABLE
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
        TIMER0_InterruptEnable();
        TMR0_InterruptHandler=_timer->TMR0_InterruptHandler;
        #endif
        /* Enable the TIMER0 */
        TIMER0_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret;
}
#endif
/**
 * @brief :deinitializes TIMER0
 * @param : _timer -> pointer to (timer0_config_t) TIMER0 configurations structure @ref timer0_config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if TIMER0_CONFIG==ENABLE
Std_ReturnType Timer0_DeInit(const timer0_config_t *_timer){
    
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the TIMER0 */
        TIMER0_MODULE_DISABLE();
        /* Disable  TIMER0 interrupt*/
        #if TIMER0_INTERRUPT_FEATURE==ENABLE
        TIMER0_InterruptDisable();
        #endif
        ret = E_OK;
    }
    return ret;
}
#endif
/**
 * @brief :Write value on TIMER0 registers TMR0L and TMR0H
 * @Preconditions :Timer0_Init() function should have been called before calling this function.
 * @param : _timer -> pointer to (timer0_config_t) TIMER0 configurations structure @ref timer0_config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if TIMER0_CONFIG==ENABLE
Std_ReturnType Timer0_Write_Value(const timer0_config_t *_timer, uint16 _value){
    
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR0H = (_value) >> 8;
        TMR0L = (uint8)(_value);
        ret = E_OK;
    }
    return ret;
}
#endif
/**
 * @brief :read value from TIMER0 registers TMR0L and TMR0H
 * @Preconditions :Timer0_Init() function should have been called before calling this function.
 * @param : _timer -> pointer to (timer0_config_t) TIMER0 configurations structure @ref timer0_config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if TIMER0_CONFIG==ENABLE
Std_ReturnType Timer0_Read_Value(const timer0_config_t *_timer, uint16 *_value){
    
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_value = 0, h_value = 0;
    if((NULL == _timer) || (NULL == _value)){
        ret = E_NOT_OK;
    }
    else{
        l_value = TMR0L;
        h_value = TMR0H;
        *_value = (uint16)((h_value << 8) + l_value);
        ret = E_OK;
    }
    return ret;
}
#endif

static inline void Timer0_Prescaler_Config(const timer0_config_t *_timer){
    if(TIMER0_PRESCALER_ENABLE_CFG == _timer->prescaler_enable){
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS = _timer->prescaler_value;
    }
    else if(TIMER0_PRESCALER_DISABLE_CFG == _timer->prescaler_enable){
        TIMER0_PRESCALER_DISABLE();
    }
}

static inline void Timer0_Mode_Select(const timer0_config_t *_timer){
    if(TIMER0_TIMER_MODE == _timer->timer0_mode){
        TIMER0_TIMER_MODE_ENABLE();
    }
    else if(TIMER0_COUNTER_MODE == _timer->timer0_mode){
        TIMER0_COUNTER_MODE_ENABLE();
        if(TIMER0_COUNTER_RISING_EDGE_CFG == _timer->timer0_counter_edge){
            TIMER0_RISING_EDGE_ENABLE();
        }
        else if(TIMER0_COUNTER_FALLING_EDGE_CFG == _timer->timer0_counter_edge){
            TIMER0_FALLING_EDGE_ENABLE();
        }
    }
}

static inline void Timer0_Register_Size_Config(const timer0_config_t *_timer){
    if(TIMER0_8BIT_REGISTER_MODE == _timer->timer0_register_size){
        TIMER0_8BIT_REGISTER_MODE_ENABLE();
    }
    else if(TIMER0_16BIT_REGISTER_MODE == _timer->timer0_register_size){
        TIMER0_16BIT_REGISTER_MODE_ENABLE();
    }
}

/*
 * Internal Interrupt TIMER0 MCAL Helper function 
 */
void TMR0_ISR(void){
    //clear TIMER0 interrupt flag
    TIMER0_InterruptFlagClear();
    //restore prescaler value
    TMR0H = (timer0_preload) >> 8;
    TMR0L = (uint8)(timer0_preload);
    //Application Callback function gets called every time this ISR executes
    if(TMR0_InterruptHandler){TMR0_InterruptHandler();}
}