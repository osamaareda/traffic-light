/*
 * File:   lcd.c
 * Author: osama reda
 *
 * Created on October 1, 2023, 12:18 AM
 */

#include"lcd.h"
#if MODE==_4_BIT_MODE
uint8 n=4;
#endif
#if MODE==_8_BIT_MODE

uint8 n=8;
#endif
static Std_ReturnType lcd_send_nbits(lcd_config_t *lcd, uint8 data_or_command);

static Std_ReturnType lcd_send_enable(lcd_config_t *lcd);

static Std_ReturnType lcd_set_curser(lcd_config_t *lcd, uint8 row, uint8 column);

/**
 * @brief  : initialize lcd
 * @param  : lcd -> pointer to (lcd_config_t) structure @ref lcd_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if LCD_CONFIG==ENABLE
Std_ReturnType lcd_init(lcd_config_t *lcd){

    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    Std_ReturnType lcd_ret=E_NOT_OK;
    uint8 pins_counter;
    if(NULL==lcd){
        ret=E_NOT_OK;
    }
    else{
        gpio_ret=gpio_pin_output_low_init(&(lcd->lcd_en));
        gpio_ret=gpio_pin_output_low_init(&(lcd->lcd_rs));
        for(pins_counter=0;pins_counter<n;pins_counter++){
            gpio_ret=gpio_pin_output_low_init(&(lcd->lcd_pins[pins_counter]));
        }
        __delay_ms(20);
        lcd_ret=lcd_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        lcd_ret=lcd_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(150);
        lcd_ret=lcd_send_command(lcd, _LCD_8BIT_MODE_2_LINE);

        lcd_ret=lcd_send_command(lcd, _LCD_CLEAR);
        lcd_ret=lcd_send_command(lcd, _LCD_RETURN_HOME);
        lcd_ret=lcd_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        lcd_ret=lcd_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        lcd_ret=lcd_send_command(lcd, _LCD_DDRAM_START);
        #if MODE==_4_BIT_MODE
        lcd_ret=lcd_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
        #endif
        #if MODE==_8_BIT_MODE
        lcd_ret=lcd_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        #endif
        ret=E_OK;
    }

    return ret;
}
#endif
/**
 * @brief  : send command to lcd
 * @param  : lcd -> pointer to (lcd_config_t) structure @ref lcd_config_t
 * @param  : command -> uint8 variables @ref uint8
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if LCD_CONFIG==ENABLE
Std_ReturnType lcd_send_command(lcd_config_t *lcd, uint8 command){

    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    Std_ReturnType lcd_ret=E_NOT_OK;
    if(NULL==lcd){
        ret=E_NOT_OK;
    }
    else{
        #if MODE==_4_BIT_MODE
        gpio_ret=gpio_pin_logic_write(&(lcd->lcd_rs),LOW);
        lcd_ret=lcd_send_nbits(lcd,command>>4);
        lcd_ret=lcd_send_enable(lcd);
        lcd_ret=lcd_send_nbits(lcd,command);
        lcd_ret=lcd_send_enable(lcd);
        #endif
        #if MODE==_8_BIT_MODE
        gpio_ret=gpio_pin_logic_write(&(lcd->lcd_rs),LOW);
        lcd_ret=lcd_send_nbits(lcd,command);
        lcd_ret=lcd_send_enable(lcd);
        #endif

        ret=E_OK;
    }

    return ret;
}
#endif
/**
 * @brief  : send char data to lcd
 * @param  : lcd -> pointer to (lcd_config_t) structure @ref lcd_config_t
 * @param  : data -> uint8 variables @ref uint8
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if LCD_CONFIG==ENABLE
Std_ReturnType lcd_send_char_data(lcd_config_t *lcd, uint8 data){

    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    Std_ReturnType lcd_ret=E_NOT_OK;
    if(NULL==lcd){
        ret=E_NOT_OK;
    }
    else{
        #if MODE==_4_BIT_MODE
        gpio_ret=gpio_pin_logic_write(&(lcd->lcd_rs),HIGH);
        lcd_ret=lcd_send_nbits(lcd,data>>4);
        lcd_ret=lcd_send_enable(lcd);
        lcd_ret=lcd_send_nbits(lcd,data);
        lcd_ret=lcd_send_enable(lcd);
        #endif
        #if MODE==_8_BIT_MODE
        gpio_ret=gpio_pin_logic_write(&(lcd->lcd_rs),HIGH);
        lcd_ret=lcd_send_nbits(lcd,data);
        lcd_ret=lcd_send_enable(lcd);
        #endif
        ret=E_OK;
    }

    return ret;
}
#endif
/**
 * @brief  : send char data to lcd  with position
 * @param  : lcd -> pointer to (lcd_config_t) structure @ref lcd_config_t
 * @param  : row,column,data -> uint8 variables @ref uint8
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if LCD_CONFIG==ENABLE
Std_ReturnType lcd_send_char_data_pos(lcd_config_t *lcd, uint8 row, uint8 column, uint8 data){

    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    Std_ReturnType lcd_ret=E_NOT_OK;
    if(NULL==lcd || row>4 || column>20){
        ret=E_NOT_OK;
    }
    else{
        lcd_ret=lcd_set_curser(lcd, row, column);
        lcd_ret=lcd_send_char_data(lcd, data);
        ret=E_OK;
    }

    return ret;
}
#endif
/**
 * @brief  : send string to lcd
 * @param  : lcd -> pointer to (lcd_config_t) structure @ref lcd_config_t
 * @param  : str -> pointer to uint8 @ref uint8
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if LCD_CONFIG==ENABLE
Std_ReturnType lcd_send_string(lcd_config_t *lcd, uint8 *str){

    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    Std_ReturnType lcd_ret=E_NOT_OK;
    if(NULL==lcd || NULL==str){
        ret=E_NOT_OK;
    }
    else{
        while(*str){
            lcd_ret=lcd_send_char_data(lcd,*str++);
        }

        ret=E_OK;
    }

    return ret;
}
#endif
/**
 * @brief  : send string to lcd  with position
 * @param  : lcd -> pointer to (lcd_config_t) structure @ref lcd_config_t
 * @param  : row,column -> uint8 variables @ref uint8
 * @param  : str -> pointer to uint8 @ref uint8
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if LCD_CONFIG==ENABLE
Std_ReturnType lcd_send_string_pos(lcd_config_t *lcd, uint8 row, uint8 column, uint8 *str){

    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    Std_ReturnType lcd_ret=E_NOT_OK;
    if(NULL==lcd || NULL==str || row>4 || column>40){
        ret=E_NOT_OK;
    }
    else{
        lcd_ret=lcd_set_curser(lcd,row,column);
        lcd_ret=lcd_send_string(lcd,str);
        ret=E_OK;
    }

    return ret;
}
#endif
/**
 * @brief  : send custom char to lcd
 * @param  : lcd -> pointer to (lcd_config_t) structure @ref lcd_config_t
 * @param  : row,column,mem_pos -> uint8 variables @ref uint8
 * @param  : _chr[] -> array of uint8 @ref uint8
 * @param  : str -> pointer to uint8 @ref uint8
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if LCD_CONFIG==ENABLE
Std_ReturnType lcd_send_custom_char(lcd_config_t *lcd, uint8 row, uint8 column,
                                          uint8 _chr[], uint8 mem_pos){

    static uint8 counter;
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    Std_ReturnType lcd_ret=E_NOT_OK;
    if(NULL==lcd || row>4 || column>20){
        ret=E_NOT_OK;
    }
    else{
        lcd_ret=lcd_send_command(lcd,(_LCD_CGRAM_START+(mem_pos*8)));
        for(counter=0;counter<8;counter++){
            lcd_ret=lcd_send_char_data(lcd, _chr[counter]);
        }
        lcd_ret=lcd_send_char_data_pos(lcd,row,column,mem_pos);

        ret=E_OK;
    }


    return ret;
}
#endif
/**
 * @brief  : send custom char to lcd
 * @param  : lcd -> pointer to (lcd_config_t) structure @ref lcd_config_t
 * @param  : row,column,mem_pos -> uint8 variables @ref uint8
 * @param  : _chr[] -> array of uint8 @ref uint8
 * @param  : str -> pointer to uint8 @ref uint8
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if LCD_CONFIG==ENABLE
Std_ReturnType lcd_send_number(lcd_config_t *lcd,uint16 num){

    static uint8 number[]={0};
    static uint8 i=0;
    static uint8 counter=0;
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    Std_ReturnType lcd_ret=E_NOT_OK;
    if(NULL==lcd){
        ret=E_NOT_OK;
    }
    else{
        convert_uint16_to_string(num,number);
        lcd_send_string(lcd,number);
    }

    return ret;
}
#endif
#if LCD_CONFIG==ENABLE
Std_ReturnType lcd_send_number_pos(lcd_config_t *lcd, uint8 row, uint8 column,uint16 num){

    static uint8 number[]={0};
    static uint8 i=0;
    static uint8 counter=0;
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    Std_ReturnType lcd_ret=E_NOT_OK;
    if(NULL==lcd){
        ret=E_NOT_OK;
    }
    else{
        convert_uint16_to_string(num,number);
        lcd_send_string_pos(lcd,row,column,number);
    }

    return ret;
}
#endif
/**
 * 
 * @param value
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{    
        memset((char *)str, '\0', 4);
        sprintf(str, "%i", value);
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str){
    Std_ReturnType ret = E_OK;
    uint8 Temp_String[6] = {0};
    uint8 DataCounter = 0;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{    
        memset(str, ' ', 5);
        str[5] = '\0';
        sprintf((char *)Temp_String, "%i", value);
        while(Temp_String[DataCounter] != '\0'){
            str[DataCounter] = Temp_String[DataCounter]; 
            DataCounter++;
        }
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{    
        memset((char *)str, '\0', 11);
        sprintf(str, "%i", value);
    }
    return ret;
}


static Std_ReturnType lcd_send_nbits(lcd_config_t *lcd, uint8 data_or_command){

    uint8 pin_counter;
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    for(pin_counter=0;pin_counter<n;pin_counter++){
        gpio_ret=gpio_pin_logic_write(&(lcd->lcd_pins[pin_counter]),(data_or_command>>pin_counter)&0x01);
    }

    return ret;
}

static Std_ReturnType lcd_send_enable(lcd_config_t *lcd){

    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    gpio_ret=gpio_pin_logic_write(&(lcd->lcd_en),HIGH);
    __delay_us(5);
    gpio_ret=gpio_pin_logic_write(&(lcd->lcd_en),LOW);

    return ret;
}


static Std_ReturnType lcd_set_curser(lcd_config_t *lcd, uint8 row, uint8 column){

    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    Std_ReturnType lcd_ret=E_NOT_OK;
	column--;
    #if SCREEN_SIZE==_2_x_40
    switch(row){
        case ROW1 :lcd_ret=lcd_send_command(lcd, 0x80+column); break;
        case ROW2 :lcd_ret=lcd_send_command(lcd, 0xc0+column); break;
    }
    #endif
    #if SCREEN_SIZE==_4_x_20
    switch(row){
        case ROW1 :lcd_ret=lcd_send_command(lcd, 0x80+column); break;
        case ROW2 :lcd_ret=lcd_send_command(lcd, 0xc0+column); break;
        case ROW3 :lcd_ret=lcd_send_command(lcd, 0x94+column); break;
        case ROW4 :lcd_ret=lcd_send_command(lcd, 0xd4+column); break;
    }
    #endif

    return ret;
}