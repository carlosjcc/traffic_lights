#include "tm4c123gh6pm.h"


void go_east(void){
    GPIO_PORTB_DATA_R = 0x0C;
    GPIO_PORTF_DATA_R = 0x02;  // set lights
}


void wait_east(void){
    GPIO_PORTB_DATA_R = 0x14;
    GPIO_PORTF_DATA_R = 0x02;
}


void go_north(void){
    GPIO_PORTB_DATA_R = 0x21;
    GPIO_PORTF_DATA_R = 0x02;
}


void wait_north(void){
    GPIO_PORTB_DATA_R = 0x22;
    GPIO_PORTF_DATA_R = 0x02;
}


void walk(void){
    GPIO_PORTB_DATA_R = 0x24;
    GPIO_PORTF_DATA_R = 0x08;
}


