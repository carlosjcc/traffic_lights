#ifndef __FSM_H__
#define __FSM_H__


// Linked data structure
typedef struct state_struct {
    void (*traffic_lights)(void);
    unsigned long time;
    //unsigned long next[5];
    unsigned long next[8];
} state;


void go_east(void);
void wait_east(void);
void go_north(void);
void wait_north(void);
void no_cars_dont_walk(void);
void no_cars_walk(void);
void no_cars_walk_off(void);
unsigned long read_sensors(void);
void fsm_controller(void);


#endif
