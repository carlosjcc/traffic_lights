#ifndef FSM_H
#define FSM_H


#define GO_EAST   0
#define WAIT_EAST 1
#define GO_NORTH   2
#define WAIT_NORTH 3
#define WALK 4


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


const state fsm[5] = {
    {&go_east, 0x00FFFFFF, {WAIT_EAST}},
    {&wait_east, 0x00FFFFFF, {GO_NORTH}},
    {&go_north, 0x00FFFFFF, {WAIT_NORTH}},
    {&wait_north, 0x00FFFFFF, {WALK}},
    {&walk, 0x00FFFFFF, {GO_EAST}}
};


#endif
