// ***** 0. Documentation Section *****
// TableTrafficLight.c for Lab 10
// Runs on LM4F120/TM4C123
// Index implementation of a Moore finite state machine to operate a traffic light.  
// Daniel Valvano, Jonathan Valvano
// January 15, 2016

// east/west red light connected to PB5
// east/west yellow light connected to PB4
// east/west green light connected to PB3
// north/south facing red light connected to PB2
// north/south facing yellow light connected to PB1
// north/south facing green light connected to PB0
// pedestrian detector connected to PE2 (1=pedestrian present)
// north/south car detector connected to PE1 (1=car present)
// east/west car detector connected to PE0 (1=car present)
// "walk" light connected to PF3 (built-in green LED)
// "don't walk" light connected to PF1 (built-in red LED)

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"

#include "io.h"
#include "systick.h"
#include "fsm.h"

// ***** 2. Global Declarations Section *****

// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts


// ***** 3. Subroutines Section *****
unsigned long s;  // index to the current state 

int main(void){
    TExaS_Init(SW_PIN_PE210, LED_PIN_PB543210,ScopeOff); // activate grader and set system clock to 80 MHz
    EnableInterrupts();

    //systick_init(); // initialize SysTick, runs at 16 MHz
    port_f_init();
    port_b_init();
    systick_init();

    s = go_east;
    while(1) {
        GPIO_PORTB_DATA_R = fsm[s].cross_roads;  // set lights
        GPIO_PORTF_DATA_R = fsm[s].walk_way;  // set lights
        systick_wait(fsm[s].time);
        systick_wait(fsm[s].time);
        //Input = SENSOR;     // read sensors
        s = fsm[s].next[0];
    }
}

