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
    GPIO_PORTF_DATA_R = 0x02;
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


void no_cars_dont_walk(void){
    GPIO_PORTB_DATA_R = 0x24;
    GPIO_PORTF_DATA_R = 0x02;
}
void no_cars_walk(void){
    GPIO_PORTB_DATA_R = 0x24;
    GPIO_PORTF_DATA_R = 0x08;
}
void no_cars_walk_off(void){
    GPIO_PORTB_DATA_R = 0x24;
    GPIO_PORTF_DATA_R = 0x00;
}


unsigned long read_sensors(void) {
    return GPIO_PORTE_DATA_R;
}

void fsm_controller(void) {
    unsigned long s;  // index to the current state
    unsigned long sensors;
    
    const state fsm[11] = {
        {&go_east, 0x00FFFFFF,    {GO_EAST,GO_EAST,WAIT_EAST,WAIT_EAST,WAIT_EAST,WAIT_EAST,WAIT_EAST,WAIT_EAST}},
        {&wait_east, 0x00FFFFFF,  {GO_EAST,GO_NORTH,GO_NORTH,GO_NORTH,WALK,WALK,WALK,GO_NORTH}},
        {&go_north, 0x00FFFFFF,   {GO_NORTH,WAIT_NORTH,GO_NORTH,WAIT_NORTH,WAIT_NORTH,WAIT_NORTH,WAIT_NORTH,WAIT_NORTH}},
        {&wait_north, 0x00FFFFFF, {GO_NORTH,GO_EAST,GO_NORTH,GO_EAST,WALK,WALK,WALK,WALK}},
        {&no_cars_walk, 0x00FFFFFF,       {WALK,BLINK_1,BLINK_1,BLINK_1,WALK,BLINK_1,BLINK_1,BLINK_1}},
        {&no_cars_dont_walk, 0x00FFFFFF,    {WALK,BLINK_2,BLINK_2,BLINK_2,WALK,BLINK_2,BLINK_2,BLINK_2}},
        {&no_cars_walk_off, 0x00FFFFFF,   {WALK,BLINK_3,BLINK_3,BLINK_3,WALK,BLINK_3,BLINK_3,BLINK_3}},
        {&no_cars_dont_walk, 0x00FFFFFF,    {WALK,BLINK_4,BLINK_4,BLINK_4,WALK,BLINK_4,BLINK_4,BLINK_4}},
        {&no_cars_walk_off, 0x00FFFFFF,   {WALK,BLINK_5,BLINK_5,BLINK_5,WALK,BLINK_5,BLINK_5,BLINK_5}},
        {&no_cars_dont_walk, 0x00FFFFFF,    {WALK,BLINK_6,BLINK_6,BLINK_6,WALK,BLINK_6,BLINK_6,BLINK_6}},
        {&no_cars_walk_off, 0x00FFFFFF,   {WALK,GO_EAST,GO_NORTH,GO_EAST,WALK,GO_EAST,GO_NORTH,GO_EAST}},
    };


    port_b_init();
    port_e_init();
    port_f_init();
    systick_init();

    s = GO_EAST;
    while(1) {
        
        sensors = read_sensors();
        
        (fsm[s].traffic_lights)();
        systick_wait(fsm[s].time);
        systick_wait(fsm[s].time);
        
        s = fsm[s].next[sensors];
    }
}
