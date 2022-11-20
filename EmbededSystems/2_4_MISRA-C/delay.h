#ifndef DELAY_H
#define DELAY_H

	#include <stm32f4xx_syscfg.h>
	void TimingDelay_Decrement(void);
	void Delay(__IO uint32_t nTime);
	
#endif