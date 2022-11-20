#include "delay.h"

RCC_ClocksTypeDef RCC_Clocks;
static volatile uint32_t TimingDelay;

void delay_ms(volatile uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

void timingDelay_Decrement(void){
  if (TimingDelay != 0x00){ 
    TimingDelay--;
  }
}

