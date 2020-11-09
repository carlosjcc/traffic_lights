#include "io.h"
#include "fsm.h"
#include "systick.h"
#include "tm4c123gh6pm.h"

#define GO_EAST   0
#define WAIT_EAST 1
#define GO_NORTH   2
#define WAIT_NORTH 3
#define WALK 4
#define BLINK_1 5
#define BLINK_2 6
#define BLINK_3 7
#define BLINK_4 8
#define BLINK_5 9
#define BLINK_6 10

void go_east(void){
    GPIO_PORTB_DATA_R = 0x0C;
}


void wait_east(void){
    GPIO_PORTB_DATA_R = 0x14;
}


void go_north(void){
    GPIO_PORTB_DATA_R = 0x21;
}


void wait_north(void){
    GPIO_PORTB_DATA_R = 0x22;
}

void no_cars(void){
        GPIO_PORTB_DATA_R = 0x24;
}


void walk(void){
    GPIO_PORTF_DATA_R = 0x08;
}

void no_walk(void){
    GPIO_PORTF_DATA_R = 0x02;
}

unsigned long read_sensors(void) {
    return GPIO_PORTE_DATA_R;
}

void fsm_controller(void) {
    unsigned long s;  // index to the current state
    unsigned long sensors;
    
    const state fsm[5] = {
        {&go_east, &no_walk, 0x00FFFFFF, {WAIT_EAST}},
        {&wait_east, &no_walk, 0x00FFFFFF, {GO_NORTH}},
        {&go_north, &no_walk, 0x00FFFFFF, {WAIT_NORTH}},
        {&wait_north, &no_walk, 0x00FFFFFF, {WALK}},
        {&no_cars, &walk, 0x00FFFFFF, {GO_EAST}}
    };


    port_b_init();
    port_e_init();
    port_f_init();
    systick_init();

    s = GO_EAST;
    while(1) {
        
        sensors = read_sensors();
        
        (fsm[s].car_lights)();
        (fsm[s].pedestrian_lights)();
        systick_wait(fsm[s].time);
        systick_wait(fsm[s].time);
        
        s = fsm[s].next[0];
    }
}
