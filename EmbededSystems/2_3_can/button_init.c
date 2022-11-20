#include "button_init.h"

RCC_ClocksTypeDef RCC_Clocks;

void ButtonInit() {
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
}

void it_init() {
		//set interrupt port    port   / out port
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0); //associate PA0 with EXTI0
  
															//external interrupt
		EXTI_InitTypeDef exti;   //create struct for working with EXTI_IMR & EXTI_RTSR registers
    exti.EXTI_Line = EXTI_Line0;    
    exti.EXTI_Mode = EXTI_Mode_Interrupt;    //EXTI_IMR ? EXTI_EMR means event or interrapts
    exti.EXTI_Trigger =   EXTI_Trigger_Rising_Falling;//EXTI_Trigger_Rising(Falling/Rizing_Falling)
    exti.EXTI_LineCmd = ENABLE;    //set state
    EXTI_Init(&exti);
	
														//nested vector interrupt controller
    NVIC_InitTypeDef nvic; // set params for contoller vector interrupts
    nvic.NVIC_IRQChannel = EXTI0_IRQn;   // set Chanal IRG for activation/disactivation
    nvic.NVIC_IRQChannelPreemptionPriority = 13;  
    nvic.NVIC_IRQChannelSubPriority = 13; 
    nvic.NVIC_IRQChannelCmd = ENABLE;  //set activity
    NVIC_Init(&nvic);
}
