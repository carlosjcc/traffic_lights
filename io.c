#include "io.h"

#define ACTIVATE_CLOCK_PORT_B 0x00000002
#define ACTIVATE_CLOCK_PORT_F 0x00000020
#define UNLOCK_GPIO_PORT 0x4C4F434B
#define ALLOW_CHANGES_PIN_2_F 0x02
#define ALLOW_CHANGES_TO_PORT_B 0x0000003F

/*
 *
 *
 */
void port_f_init(void) {
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= 0x00000020;     // 1) activate clock for Port F
    delay = SYSCTL_RCGC2_R;           // allow time for clock to start
    GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
    GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF2
    // only PF0 needs to be unlocked, other bits can't be locked
    GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
    GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
    GPIO_PORTF_DIR_R = 0x0A;          // 5) PF3 PF1 out
    GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
    GPIO_PORTF_PUR_R = 0x00;          // enable pull-up on PF4
    GPIO_PORTF_DEN_R = 0x0A;          // 7) enable digital I/O on PF4-0
}

void port_b_init(void) {
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= ACTIVATE_CLOCK_PORT_B;     // 1) activate clock for Port B
    delay = SYSCTL_RCGC2_R;           // allow time for clock to start
    GPIO_PORTB_LOCK_R = UNLOCK_GPIO_PORT;   // 2) unlock GPIO Port F
    GPIO_PORTF_CR_R = ALLOW_CHANGES_TO_PORT_B;           // allow changes to PF2
    // only PF0 needs to be unlocked, other bits can't be locked
    GPIO_PORTB_AMSEL_R = 0x00;        // 3) disable analog on PF
    GPIO_PORTB_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
    // FINISH THIS
    GPIO_PORTB_DIR_R = 0x3F;          // 5) PF4 in, PF1 out
    GPIO_PORTB_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
    GPIO_PORTB_PUR_R = 0x00;          // enable pull-up on PF4
    GPIO_PORTB_DEN_R = 0x3F;          // 7) enable digital I/O on PF4-0
}
