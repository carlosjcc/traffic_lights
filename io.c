#include "io.h"

#define ACTIVATE_CLOCK_PORT_F 0x00000020
#define UNLOCK_GPIO_PORT_F 0x4C4F434B
#define ALLOW_CHANGES_PIN_2_F 0x02

/*
 * Sets PF4 as input from SW1 and PF1 as output to the led
 *
 */
void port_f_init(void) {
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= ACTIVATE_CLOCK_PORT_F;     // 1) activate clock for Port F
    delay = SYSCTL_RCGC2_R;           // allow time for clock to start
    GPIO_PORTF_LOCK_R = UNLOCK_GPIO_PORT_F;   // 2) unlock GPIO Port F
    GPIO_PORTF_CR_R = ALLOW_CHANGES_PIN_2_F;           // allow changes to PF2
    // only PF0 needs to be unlocked, other bits can't be locked
    GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
    GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
    GPIO_PORTF_DIR_R = 0x02;          // 5) PF4 in, PF1 out
    GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
    GPIO_PORTF_PUR_R = 0x10;          // enable pull-up on PF4
    GPIO_PORTF_DEN_R = 0x12;          // 7) enable digital I/O on PF4-0
}
