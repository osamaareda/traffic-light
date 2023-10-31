/* 
 * File:   GPIO.h
 * Author: osama reda
 *
 * Created on September 15, 2023, 11:30 PM
 */

#ifndef GPIO_H
#define	GPIO_H

/*-----------------------includes-------------------------*/
#include"../mcal_std_types.h"
#include"mcal_gpio_cfg.h"

/*---------------data type declaration---------------*/
//enumeration help for initialization
typedef enum
{
    LOW,
    HIGH 
}logic_t;

typedef enum
{
    OUTPUT,
    INPUT 
}direction_t;

typedef enum
{
    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}pin_index_t;

typedef enum
{
    PORTA_INDEX,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
}port_index_t;

typedef struct{
    uint8 port      : 3; /* @ref  port_index_t */
    uint8 pin       : 3; /* @ref  pin_index_t */
    uint8 direction : 1; /* @ref  direction_t */
    uint8 logic     : 1; /* @ref  logic_t */
}pin_config_t;

/*----------------macros declaration-----------------*/
//pin macros
#define BIT_MASK          (uint8)1
#define PIN_MAX_NUM              7
#define PIN_DIRECTION_MAX_VALUE  1
#define PIN_LOGIC_MAX_VALUE      1
//port macros
#define PORT_MASK                0xff
#define PORT_MAX_NUM             4
#define PORT_DIRECTIO_MAX_VALUE  0xff
#define PORT_LOGIC_MAX_VALUE     0xff
#define PORT_OUTPUT              0x00
#define PORT_INPUT               0xff
#define PORT_LOW                 0x00
#define PORT_HIGH                0xff

/*-----------macro function declaration------------*/
#define HWREG(_X)                    *((volatile uint8*)(_X)))
#define SET_BIT(REG , BIT_POS)       (REG |=  (BIT_MASK<<BIT_POS))
#define CLEAR_BIT(REG , BIT_POS)     (REG &= ~(BIT_MASK<<BIT_POS))
#define TOGGLE_BIT(REG , BIT_POS)    (REG ^=  (BIT_MASK<<BIT_POS))
#define READ_BIT(REG , BIT_POS)      ((REG>>BIT_POS)  &  BIT_MASK)

/*----------------function declaration-----------------*/
Std_ReturnType gpio_pin_direction_init(pin_config_t *pin, direction_t pin_direction);
Std_ReturnType gpio_pin_get_direction_status(pin_config_t *pin, direction_t *pin_direction_status);
Std_ReturnType gpio_pin_logic_write(pin_config_t *pin, logic_t pin_logic);
Std_ReturnType gpio_pin_logic_read(pin_config_t *pin, logic_t *pin_logic_read);
Std_ReturnType gpio_pin_toggle_logic(pin_config_t *pin);
Std_ReturnType gpio_pin_output_low_init(pin_config_t *pin);
Std_ReturnType gpio_pin_output_high_init(pin_config_t *pin);
Std_ReturnType gpio_pin_input_init(pin_config_t *pin);

Std_ReturnType gpio_port_direction_init(port_index_t port, uint8 port_direction);
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *port_direction_status);
Std_ReturnType gpio_port_logic_write(port_index_t port, uint8 port_logic);
Std_ReturnType gpio_port_logic_read(port_index_t port, uint8 *port_logic_read);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);
#endif	/* GPIO_H */