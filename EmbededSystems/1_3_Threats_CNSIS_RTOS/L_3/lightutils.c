#include "lightutils.h"
#include "stm32f4xx_hal_gpio.h"

void lightsOnOff(Color color, short state)
{
	if(state)
	{
		GPIOD->ODR |=color;
	}
	else
	{
		GPIOD->ODR &=(~color);
	}
}
