#ifndef headh
#define headh

	#include "stm32f4xx.h"

	#include "init.h"
	
	#define CHECK_BIT(var,pos) (((var)>>(pos)) & 1)
	#define SIZE 10

	// Device header
	void InterruptsInit(void);

	#include "flash_write.h"
	#include "flash_read.h"
	
	extern volatile uint16_t timeFromStart;
	//v5 To turn on the green and blue LEDs at each button pressure. 
	//If the user presses the button again, this couple of LEDs should be turned off and another 
	//couple of the LEDs should be turned on instead.
#endif
