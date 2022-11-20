#ifndef GLOBAL_DEFINES_H
#define GLOBAL_DEFINES_H

#include "stm32f4xx.h"

typedef enum
{
	GREEN = 0x1000,
	ORANGE= 0x2000,
	RED = 0x4000,
	BLUE = 0x8000
}LEDCOLORS;

void LEDSwitchOnOff(LEDCOLORS, short);
void ConfigGPIO(void);
void ConfigEXTI(void);
#define ON 1
#define OFF ~ON
#endif
