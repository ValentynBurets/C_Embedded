#include "globalDefines.h"

void LEDSwitchOnOff(LEDCOLORS color, short state)
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

void ConfigGPIO()
{
  GPIOD->MODER = 0x55000000;
  GPIOD->OSPEEDR = 0;
  GPIOD->OTYPER = 0;
  GPIOD->PUPDR = 0x0001;  
  GPIOA->MODER = 0x0000;
  GPIOA->PUPDR = 0x0001;
  
  RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIODEN);
}

void ConfigEXTI()
{
  SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
  EXTI->IMR  |= EXTI_IMR_IM0;
  EXTI->RTSR |= EXTI_RTSR_TR0;
  
  NVIC_EnableIRQ(EXTI0_IRQn);
  NVIC_SetPriority(EXTI0_IRQn,1);
}
