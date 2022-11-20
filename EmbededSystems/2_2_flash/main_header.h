#ifndef main_header_h
#define main_header_h
#include "stm32f4xx.h"
#include "init.h"

// Device header
void InterruptsInit(void);

#define CHECK_BIT(var,pos) (((var)>>(pos)) & 1)
#define SIZE 10

extern volatile uint16_t timeFromStart;
	//v5 To turn on the green and blue LEDs at each button pressure. 
	//If the user presses the button again, this couple of LEDs should be turned off and another 
	//couple of the LEDs should be turned on instead.
#endif
