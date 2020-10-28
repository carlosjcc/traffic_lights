#ifndef __FSM_H__
#define __FSM_H__





// Linked data structure
typedef struct state_struct {
    void (*set_lights)(void);
    unsigned long time;
    //unsigned long next[5];
    unsigned long next[1];
} state;


void go_east(void);
void wait_east(void);
void go_north(void);
void wait_north(void);
void walk(void);
void fsm_controller(void);


#endif
