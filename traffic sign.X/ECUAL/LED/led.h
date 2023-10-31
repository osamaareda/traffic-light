/* 
 * File:   led.h
 * Author: osama reda
 *
 * Created on September 17, 2023, 08:15 PM
 */
#ifndef LED_H
#define	LED_H

/*-----------------------includes-------------------------*/
#include"../../MCAL/GPIO/gpio.h"
#include"ecual_led_cfg.h"

/*---------------data type declaration---------------*/
typedef enum{
    LED_OFF,
    LED_ON
}led_status_t;

typedef struct{
    pin_config_t led_pin;   /* @ref  pin_config_t */
    led_status_t led_state; /* @ref  led_status_t */
}led_config_t;

/*----------------function declaration-----------------*/
Std_ReturnType led_init(led_config_t *led);
Std_ReturnType led_on(led_config_t *led);
Std_ReturnType led_off(led_config_t *led);
Std_ReturnType led_toggle(led_config_t *led);
#endif	/* LED_H */