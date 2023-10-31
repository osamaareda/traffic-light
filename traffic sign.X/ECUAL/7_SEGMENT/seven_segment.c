/* 
 * File:   seven_segment.h
 * Author: 20128
 *
 * Created on September 25, 2023, 3:08 PM
 */
#include"seven_segment.h"
/**
 * @brief  : initialize four pins to be output as decoder's pins
 * @param  : seg -> pointer to (seven_segment_config_t) structure @ref seven_segment_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if SEVEN_SEGMENT_CONFIG==ENABLE
Std_ReturnType seven_segment_init(seven_segment_config_t *seg){
    
    static uint8 counter;
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==seg){
        ret=E_NOT_OK;
    }
    else{
        for(counter=0;counter<8;counter++){
            gpio_ret=gpio_pin_output_low_init(&(seg->seven_segment_pins[counter]));
        }
        
        
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : write a number on the seven segment
 * @param  : seg -> pointer to (seven_segment_config_t) structure @ref seven_segment_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if SEVEN_SEGMENT_CONFIG==ENABLE
Std_ReturnType seven_segment_write(seven_segment_config_t *seg, uint8 num){
    
    static uint8 counter;
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==seg || num>9){
        ret=E_NOT_OK;
    }
    else{
        for(counter=0;counter<8;counter++){
             gpio_pin_logic_write(&(seg->seven_segment_pins[counter]),(num>>counter)&0x1);
        
        }
        
        ret=E_OK;
    }
    
    return ret;
}
#endif