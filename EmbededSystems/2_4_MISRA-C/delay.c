#include "delay.h"

static __IO uint32_t startDelay = 1000;
static __IO uint32_t _tempTimingDelay;
 
void Delay(__IO uint32_t nTime)
{ 
  _tempTimingDelay = nTime;

  while(_tempTimingDelay != 0);
}

void TimingDelay_Decrement(void){
  if (_tempTimingDelay != 0x00){ 
    _tempTimingDelay--;
  }
}
