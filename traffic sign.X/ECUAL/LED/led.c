/* 
 * File:   led.c
 * Author: osama reda
 *
 * Created on September 17, 2023, 08:15 PM
 */

#include"led.h"
/**
 * @brief  : initialize led to be output and off
 * @param  : led -> pointer to (led_config_t) structure @ref led_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if LED_CONFIG==ENABLE
Std_ReturnType led_init(led_config_t *led){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==led){
        ret=E_NOT_OK;
    }
    else{
        gpio_ret=gpio_pin_output_low_init(&(led->led_pin));
        led->led_state=led->led_pin.logic;
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : turn the led on
 * @param  : led -> pointer to (led_config_t) structure @ref led_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if LED_CONFIG==ENABLE
Std_ReturnType led_on(led_config_t *led){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==led){
        ret=E_NOT_OK;
    }
    else{
        gpio_ret=gpio_pin_logic_write(&(led->led_pin),HIGH);
        led->led_state=led->led_pin.logic;
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : turn the led off
 * @param  : led -> pointer to (led_config_t) structure @ref led_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if LED_CONFIG==ENABLE
Std_ReturnType led_off(led_config_t *led){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==led){
        ret=E_NOT_OK;
    }
    else{
        gpio_ret=gpio_pin_logic_write(&(led->led_pin),LOW);
        led->led_state=led->led_pin.logic;
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : toggle the led 
 * @param  : led -> pointer to (led_config_t) structure @ref led_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if LED_CONFIG==ENABLE
Std_ReturnType led_toggle(led_config_t *led){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==led){
        ret=E_NOT_OK;
    } 
    else{
        gpio_ret=gpio_pin_toggle_logic(&(led->led_pin));
        ret=E_OK;
    }
    
    return ret;
}
#endif