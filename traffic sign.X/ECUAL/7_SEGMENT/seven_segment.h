
/* 
 * File:   seven_segment.h
 * Author: 20128
 *
 * Created on September 25, 2023, 3:08 PM
 */

#ifndef seven_SEGMENT_H
#define seven_SEGMENT_H

/*-----------------------includes-------------------------*/
#include"../../MCAL/GPIO/gpio.h"
#include"ecual_7_segment_cfg.h"

/*---------------data type declaration---------------*/
typedef enum{
    COMMON_ANODE,
    COMMON_CATHODE
}seven_segment_type_t;

typedef struct{
    pin_config_t seven_segment_pins[4];      /* @ref  pin_config_t */
    seven_segment_type_t segment_type;    /* @ref  relay_state_t */
}seven_segment_config_t;

/*----------------function declaration-----------------*/
Std_ReturnType seven_segment_init(seven_segment_config_t *seg);
Std_ReturnType seven_segment_write(seven_segment_config_t *seg, uint8 num);
#endif	/* seven_SEGMENT_H */