/* 
 * File:   ecual_lcd_cfg.h
 * Author: osama reda
 *
 * Created on October 1, 2023, 12:19 AM
 */

#ifndef ECUAL_LCD_CFG_H
#define	ECUAL_LCD_CFG_H

/*----------------macros declaration-----------------*/
//bit mode configuration
#define _4_BIT_MODE   1
#define _8_BIT_MODE   0
#define MODE           _4_BIT_MODE
//screen size configuration
#define _4_x_20       1
#define _2_x_40       0
#define SCREEN_SIZE    _4_x_20
//function configuration
#define ENABLE             1
#define DISABLE            0
#define STATE              ENABLE
#define LCD_CONFIG         STATE
#endif	/* ECUAL_LCD_CFG_H */