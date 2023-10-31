/* 
 * File:   init.c
 * Author: osama reda
 *
 * Created on October 31, 2023, 4:10 AM
 */
#include "init.h"

/*============================leds configuration===========================*/
//traffic red led
led_config_t led_red={.led_pin.port=PORTC_INDEX,.led_pin.pin=PIN0};
//traffic yellow led
led_config_t led_yellow={.led_pin.port=PORTC_INDEX,.led_pin.pin=PIN1};
//traffic green led
led_config_t led_green={.led_pin.port=PORTC_INDEX,.led_pin.pin=PIN2};

/*============================timer0 configuration==========================*/
timer0_config_t timer0={
    .TMR0_InterruptHandler=MY_TMR0_ISR,
    .prescaler_enable=TIMER0_PRESCALER_ENABLE_CFG,
    .prescaler_value=TIMER0_PRESCALER_DIV_BY_32,
    .timer0_mode=TIMER0_TIMER_MODE,
    .timer0_register_size=TIMER0_16BIT_REGISTER_MODE,
    .timer0_preload_value=3036
};
/*===========================7-segment configuration=========================*/
//ones red counter
seven_segment_config_t seg_red1={.seven_segment_pins[0].port=PORTD_INDEX,.seven_segment_pins[0].pin=PIN0,
                                 .seven_segment_pins[1].port=PORTD_INDEX,.seven_segment_pins[1].pin=PIN1,
                                 .seven_segment_pins[2].port=PORTD_INDEX,.seven_segment_pins[2].pin=PIN2,
                                 .seven_segment_pins[3].port=PORTD_INDEX,.seven_segment_pins[3].pin=PIN3};

//tens red counter
seven_segment_config_t seg_red2={.seven_segment_pins[0].port=PORTD_INDEX,.seven_segment_pins[0].pin=PIN4,
                                 .seven_segment_pins[1].port=PORTD_INDEX,.seven_segment_pins[1].pin=PIN5,
                                 .seven_segment_pins[2].port=PORTD_INDEX,.seven_segment_pins[2].pin=PIN6,
                                 .seven_segment_pins[3].port=PORTD_INDEX,.seven_segment_pins[3].pin=PIN7};

//ones green counter
seven_segment_config_t seg_green1={.seven_segment_pins[0].port=PORTB_INDEX,.seven_segment_pins[0].pin=PIN0,
                                   .seven_segment_pins[1].port=PORTB_INDEX,.seven_segment_pins[1].pin=PIN1,
                                   .seven_segment_pins[2].port=PORTB_INDEX,.seven_segment_pins[2].pin=PIN2,
                                   .seven_segment_pins[3].port=PORTB_INDEX,.seven_segment_pins[3].pin=PIN3};  
  

//tens green counter
seven_segment_config_t seg_green2={.seven_segment_pins[0].port=PORTB_INDEX,.seven_segment_pins[0].pin=PIN4,
                                   .seven_segment_pins[1].port=PORTB_INDEX,.seven_segment_pins[1].pin=PIN5,
                                   .seven_segment_pins[2].port=PORTB_INDEX,.seven_segment_pins[2].pin=PIN6,
                                   .seven_segment_pins[3].port=PORTB_INDEX,.seven_segment_pins[3].pin=PIN7};  

void init(void){
    Std_ReturnType ret=E_NOT_OK;
    //led initialization
    ret=led_init(&led_red);
    ret=led_init(&led_yellow);
    ret=led_init(&led_green);
    //timer0 initialization
    ret=Timer0_Init(&timer0);
    //7 segment initializiation
    ret=seven_segment_init(&seg_red1);
    ret=seven_segment_init(&seg_red2);
    ret=seven_segment_init(&seg_green1);
    ret=seven_segment_init(&seg_green2);
    
}
