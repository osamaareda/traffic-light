/* 
 * File:   app.c
 * Author: osama reda
 *
 * Created on October 31, 2023, 4:10 AM
 */

#include"app.h"
Std_ReturnType ret=E_NOT_OK;

volatile uint8 red_counter=60,green_counter=61;

/*=============================main code===============================*/   
int main() {
    //component initialization
    init();
   
while(1)
{

}
    return (EXIT_SUCCESS);
}
/**
 * 
 * applicatios ISR for TIMER0 take place every one seconde
 */
void MY_TMR0_ISR(void){
    /*********red traffic*********/
    if(red_counter<=60 && red_counter>=30){
        led_on(&led_red);
        led_off(&led_green);
        //red counter
        if(red_counter<=9){
            seven_segment_write(&seg_red1,red_counter);
        }
        else {
            seven_segment_write(&seg_red2,(red_counter/10)-3);
            seven_segment_write(&seg_red1,(red_counter%10));
        }
    }
    if(red_counter<=35 && red_counter>=31){
        led_on(&led_yellow);
    }
    
    if(red_counter<=30){ //decrement green counter
        green_counter--;
    }
    
    /*********green traffic*********/
    if(green_counter<=60 && green_counter>=31){
        seven_segment_write(&seg_red2,0);
        seven_segment_write(&seg_red1,0);
        led_off(&led_red);
        led_off(&led_yellow);
        led_on(&led_green);
        //green counter
        if(green_counter<=9){
            seven_segment_write(&seg_green1,green_counter);
        }
        else {
            seven_segment_write(&seg_green2,(green_counter/10)-3);
            seven_segment_write(&seg_green1,(green_counter%10));
        }
    }
    if(green_counter<=35 && green_counter>=31){
        led_on(&led_yellow);
    }
    //back to initialization values
    if(green_counter==30){
        green_counter=61;
        red_counter=61;
        seven_segment_write(&seg_green2,0);
        seven_segment_write(&seg_green1,0);
        led_off(&led_red);
        led_off(&led_green);
        led_off(&led_yellow); 
    }
    red_counter--; //decrement red counter
}




