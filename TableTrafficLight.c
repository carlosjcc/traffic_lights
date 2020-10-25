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


// ***** 2. Global Declarations Section *****

// FUNCTION PROTOTYPES: Each subroutine defined
void disable_interrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void systick_init(void);

void systick_wait(unsigned long delay);
// ***** 3. Subroutines Section *****

unsigned long a = 0x00000000;
// first data point is wrong, the other 49 will be correct
unsigned long Time[50];
// you must leave the Data array defined exactly as it is
unsigned long Data[50];
unsigned long i;

int main(void){
    unsigned long i,last,now;

    TExaS_Init(SW_PIN_PE210, LED_PIN_PB543210,ScopeOff); // activate grader and set system clock to 80 MHz

    systick_init(); // initialize SysTick, runs at 16 MHz


    EnableInterrupts();
    while(1) {


        for (i = 0; i < 3; i++)
            systick_wait(16000000);

        a ^= 0x00000001;

        if(i<50) {
            now = NVIC_ST_CURRENT_R;
            Time[i] = (last-now)&0x00FFFFFF;  // 24-bit time difference
            Data[i] = a; // record PF1
            last = now;
            i++;
        }
    }
}


// Initialize SysTick with busy wait running at bus clock.
void systick_init(void){
    NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
    NVIC_ST_RELOAD_R = 0x00FFFFFF;        // maximum reload value
    NVIC_ST_CURRENT_R = 0;                // any write to current clears it
    NVIC_ST_CTRL_R = 0x00000005;          // enable SysTick with core clock
}

void systick_wait(unsigned long delay){
    volatile unsigned long elapsedTime;
    unsigned long startTime = NVIC_ST_CURRENT_R;
    do{
        elapsedTime = (startTime-NVIC_ST_CURRENT_R)&0x00FFFFFF;
    }
    while(elapsedTime <= delay);
}
