#include "systick.h" 
// Initialize SysTick with busy wait running at bus clock.
void systick_init(void){
    NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
    NVIC_ST_RELOAD_R = 0x00FFFFFF;        // maximum reload value
    NVIC_ST_CURRENT_R = 0;                // any write to current clears it
    NVIC_ST_CTRL_R = 0x00000005;          // enable SysTick with core clock
}


void systick_wait(unsigned long delay) {
    NVIC_ST_RELOAD_R = delay-1;  // number of counts to wait
    NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears
    while((NVIC_ST_CTRL_R&0x00010000)==0);
}
