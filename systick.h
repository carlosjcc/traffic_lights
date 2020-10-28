#ifndef __SYSTICK_H__
#define __SYSTICK_H__


#include "tm4c123gh6pm.h"

void systick_init(void);

void systick_wait(unsigned long delay);

#endif
