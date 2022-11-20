#ifndef DELAY_H
#define DELAY_H

#include <stm32f4xx.h>

void timingDelay_Decrement(void);
void delay_ms(volatile uint32_t nTime);


#endif //DELAY_H
