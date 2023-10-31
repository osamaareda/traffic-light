/*
 * File:   lcd.h
 * Author: osama reda
 *
 * Created on October 1, 2023, 12:18 AM
 */

#ifndef LCD_H
#define	LCD_H

/*-----------------------includes-------------------------*/
#include"../../MCAL/GPIO/gpio.h"
#include"ecual_lcd_cfg.h"

/*----------------macros declaration-----------------*/
#define _LCD_CLEAR                                0X01
#define _LCD_RETURN_HOME                          0x02
#define _LCD_ENTRY_MODE_DEC_SHIFT_OFF             0x04
#define _LCD_ENTRY_MODE_DEC_SHIFT_ON              0x05
#define _LCD_ENTRY_MODE_INC_SHIFT_OFF             0x06
#define _LCD_ENTRY_MODE_INC_SHIFT_ON              0x07
#define _LCD_CURSOR_MOVE_SHIFT_LEFT               0x10
#define _LCD_CURSOR_MOVE_SHIFT_RIGHT              0x14
#define _LCD_DISPLAY_SHIFT_LEFT                   0x18
#define _LCD_DISPLAY_SHIFT_RIGHT                  0x1C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF  0x0C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON   0x0D
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF   0x0E
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON    0x0F
#define _LCD_DISPLAY_OFF_CURSOR_OFF               0x08
#define _LCD_8BIT_MODE_2_LINE                     0x38
#define _LCD_4BIT_MODE_2_LINE                     0x28

#define _LCD_CGRAM_START       0x40
#define _LCD_DDRAM_START       0x80

#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4
/*---------------data type declaration---------------*/
#if MODE==_4_BIT_MODE
typedef struct{
    pin_config_t lcd_rs;       /* @ref  pin_config_t */
    pin_config_t lcd_en;       /* @ref  pin_config_t */
    pin_config_t lcd_pins[4];  /* @ref  pin_config_t */
}lcd_config_t;
#endif

#if MODE==_8_BIT_MODE
typedef struct{
    pin_config_t lcd_rs;       /* @ref  pin_config_t */
    pin_config_t lcd_en;       /* @ref  pin_config_t */
    pin_config_t lcd_pins[8];  /* @ref  pin_config_t */
}lcd_config_t;
#endif

/*----------------function declaration-----------------*/
Std_ReturnType lcd_init(lcd_config_t *lcd);
Std_ReturnType lcd_send_command(lcd_config_t *lcd, uint8 command);
Std_ReturnType lcd_send_char_data(lcd_config_t *lcd, uint8 data);
Std_ReturnType lcd_send_char_data_pos(lcd_config_t *lcd,uint8 row, uint8 column, uint8 data);
Std_ReturnType lcd_send_string(lcd_config_t *lcd, uint8 *str);
Std_ReturnType lcd_send_string_pos(lcd_config_t *lcd, uint8 row, uint8 column, uint8 *str);
Std_ReturnType lcd_send_custom_char(lcd_config_t *lcd, uint8 row, uint8 column,
                                          uint8 _chr[], uint8 mem_pos);
Std_ReturnType lcd_send_number(lcd_config_t *lcd,uint16 num);
Std_ReturnType lcd_send_number_pos(lcd_config_t *lcd, uint8 row, uint8 column,uint16 num);

Std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str);
Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str);
Std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str);
#endif	/* LCD_H */