/* 
 * File:   gpio.c
 * Author: osama reda
 *
 * Created on September 15, 2023, 11:30 PM
 */

#include"gpio.h"
//array of pointer to GPIO register
volatile uint8 *trisx[]={&TRISA, &TRISB , &TRISC , &TRISD , &TRISE};
volatile uint8 *latx[]={&LATA, &LATB , &LATC , &LATD , &LATE};
volatile uint8 *portx[]={&PORTA, &PORTB , &PORTC , &PORTD , &PORTE};

/**
 * @brief  : initialize pin to be output or input
 * @param  : pin_config -> pointer to (pin_config_t) structure @ref pin_config_t
 * @param  : pin_direction -> (direction_t) enum variable @ref direction_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if GPIO_PIN_CONFIG==ENABLE
Std_ReturnType gpio_pin_direction_init(pin_config_t *pin, direction_t pin_direction){
    
    Std_ReturnType ret=E_NOT_OK;
    if(NULL==pin || (pin->pin)>PIN_MAX_NUM || pin_direction>PIN_DIRECTION_MAX_VALUE){
        ret=E_NOT_OK;
    }
    else{
        switch(pin_direction){
            case OUTPUT :
                CLEAR_BIT(*trisx[pin->port],pin->pin);
                break;

            case INPUT  :
                SET_BIT(*trisx[pin->port],pin->pin);
                break;

            default     :
                ret=E_NOT_OK;
        }
        pin->direction=pin_direction;
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : inform me pin is output or input
 * @param  : pin_config -> pointer to (pin_config_t) structure @ref pin_config_t
 * @param  : pin_direction_status -> pointer to (direction_t) enum @ref direction_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if GPIO_PIN_CONFIG==ENABLE
Std_ReturnType gpio_pin_get_direction_status(pin_config_t *pin, direction_t *pin_direction_status){
    
    Std_ReturnType ret=E_NOT_OK;
    if(NULL==pin || NULL==pin_direction_status || (pin->pin)>PIN_MAX_NUM){
        ret=E_NOT_OK;
    }
    else{
        *pin_direction_status=READ_BIT(*trisx[pin->port],pin->pin);
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : initialize pin to be high or low
 * @param  : pin_config -> pointer to (pin_config_t) structure @ref pin_config_t
 * @param  : pin_logic -> (logic_t) enum variable @ref logic_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if GPIO_PIN_CONFIG==ENABLE
Std_ReturnType gpio_pin_logic_write(pin_config_t *pin, logic_t pin_logic){
    
    Std_ReturnType ret=E_NOT_OK;
    if(NULL==pin ||(pin->pin)>PIN_MAX_NUM || pin_logic>PIN_LOGIC_MAX_VALUE){
        ret=E_NOT_OK;
    }
    else{
        switch(pin_logic){
            case LOW    :
                CLEAR_BIT(*latx[pin->port],pin->pin);
                break;
                
            case HIGH  :
                SET_BIT(*latx[pin->port],pin->pin);
                break;

            default    :
                ret=E_NOT_OK;
        }
        pin->logic=pin_logic;
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : inform me pin is high or low
 * @param  : pin_config -> pointer to (pin_config_t) structure @ref pin_config_t
 * @param  : pin_logic_read -> pointer to (logic_t) enum @ref logic_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if GPIO_PIN_CONFIG==ENABLE
Std_ReturnType gpio_pin_logic_read(pin_config_t *pin, logic_t *pin_logic_read){
    
    Std_ReturnType ret=E_NOT_OK;
    if(NULL==pin || NULL==pin_logic_read || (pin->pin)>PIN_MAX_NUM){
        ret=E_NOT_OK;
    }
    else{
        *pin_logic_read=READ_BIT(*portx[pin->port],pin->pin);
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : change pin between high and low 
 * @param  : pin_config -> pointer to (pin_config_t) structure @ref pin_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if GPIO_PIN_CONFIG==ENABLE
Std_ReturnType gpio_pin_toggle_logic( pin_config_t *pin){
    
    Std_ReturnType ret=E_NOT_OK;
    if(NULL==pin ||(pin->pin)>PIN_MAX_NUM){
        ret=E_NOT_OK;
    }
    else{
        TOGGLE_BIT(*latx[pin->port],pin->pin);
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : initialize pin to be output and low
 * @param  : pin_config -> pointer to (pin_config_t) structure @ref pin_config_t
 * @param  : pin_direction -> (direction_t) enum variable @ref direction_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if GPIO_PIN_CONFIG==ENABLE
Std_ReturnType gpio_pin_output_low_init(pin_config_t *pin){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==pin || (pin->pin)>PIN_MAX_NUM){
        ret=E_NOT_OK;
    }
    else{
        gpio_ret=gpio_pin_direction_init(pin,OUTPUT);
        gpio_ret=gpio_pin_logic_write(pin,LOW);
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : initialize pin to be output and high
 * @param  : pin_config -> pointer to (pin_config_t) structure @ref pin_config_t
 * @param  : pin_direction -> (direction_t) enum variable @ref direction_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if GPIO_PIN_CONFIG==ENABLE
Std_ReturnType gpio_pin_output_high_init(pin_config_t *pin){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==pin || (pin->pin)>PIN_MAX_NUM){
        ret=E_NOT_OK;
    }
    else{
        gpio_ret=gpio_pin_direction_init(pin,OUTPUT);
        gpio_ret=gpio_pin_logic_write(pin,HIGH);
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : initialize pin to be input
 * @param  : pin_config -> pointer to (pin_config_t) structure @ref pin_config_t
 * @param  : pin_direction -> (direction_t) enum variable @ref direction_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if GPIO_PIN_CONFIG==ENABLE
Std_ReturnType gpio_pin_input_init(pin_config_t *pin){
    
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==pin || (pin->pin)>PIN_MAX_NUM){
        ret=E_NOT_OK;
    }
    else{
        gpio_ret=gpio_pin_direction_init(pin,INPUT); 
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : initialize all pin in the port to be output or input
 * @param  : port -> (port_index_t) enum variable @ref port_index_t
 * @param  : port_direction -> uint8 variable
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if GPIO_PORT_CONFIG==ENABLE
Std_ReturnType gpio_port_direction_init(port_index_t port, uint8 port_direction){
    
    Std_ReturnType ret=E_NOT_OK;
    if(port>PORT_MAX_NUM || port_direction>PORT_DIRECTIO_MAX_VALUE){
        ret=E_NOT_OK;
    }
    else{
        *trisx[port]=port_direction;
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : inform me all pin in the port is output or input
 * @param  : port -> (port_index_t) enum variable @ref port_index_t
 * @param  : port_direction_status -> pointer to uint8
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if GPIO_PORT_CONFIG==ENABLE
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *port_direction_status){
    
    Std_ReturnType ret=E_NOT_OK;
    if(port>PORT_MAX_NUM || NULL==port_direction_status){
        ret=E_NOT_OK;
    }
    else{
        *port_direction_status=*trisx[port];
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : initialize all pin in the port to be high or low
 * @param  : port -> (port_index_t) enum variable @ref port_index_t
 * @param  : port_logic -> uint8 variable
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if GPIO_PORT_CONFIG==ENABLE
Std_ReturnType gpio_port_logic_write(port_index_t port, uint8 port_logic){
    
    Std_ReturnType ret=E_NOT_OK;
    if(port>PORT_MAX_NUM || port_logic>PORT_LOGIC_MAX_VALUE){
        ret=E_NOT_OK;
    }
    else{
        *latx[port]=port_logic;
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : inform me all pin in the port is high or low
 * @param  : port -> (port_index_t) enum variable @ref port_index_t
 * @param  : port_logic_read -> pointer to uint8
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if GPIO_PORT_CONFIG==ENABLE
Std_ReturnType gpio_port_logic_read(port_index_t port, uint8 *port_logic_read){
    
    Std_ReturnType ret=E_NOT_OK;
    if(port>PORT_MAX_NUM || NULL==port_logic_read){
        ret=E_NOT_OK;
    }
    else{
        *port_logic_read=*portx[port];
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : change all pin in the port between high and low
 * @param  : port -> (port_index_t) enum variable @ref port_index_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if GPIO_PORT_CONFIG==ENABLE
Std_ReturnType gpio_port_toggle_logic(port_index_t port){
    
    Std_ReturnType ret=E_NOT_OK;
    if(port>PORT_MAX_NUM){
        ret=E_NOT_OK;
    }
    else{
        *latx[port]^=PORT_MASK;
        ret=E_OK;
    }
    
    return ret;
}
#endif