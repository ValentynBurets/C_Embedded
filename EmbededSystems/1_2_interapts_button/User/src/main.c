
#include "stm32f4xx.h"
#include <stm32f4xx_rcc.h>   
#include <stm32f4xx_gpio.h>  
#include <misc.h>   
#include <stm32f4xx_syscfg.h>
#include <stm32f4xx_exti.h>  //contain EXTI_InitTypeDef

RCC_ClocksTypeDef RCC_Clocks;

void ButtonInit() {
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
	
}


const uint16_t LEDS = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;

void leds_init() {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  
      GPIO_InitTypeDef gpio;   //set parameters for user leds
      GPIO_StructInit(&gpio);
      gpio.GPIO_OType = GPIO_OType_PP;   
      gpio.GPIO_Mode = GPIO_Mode_OUT;  
      gpio.GPIO_Pin = LEDS;   
      GPIO_Init(GPIOD, &gpio);
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


static __IO uint32_t startDelay = 1000;
static __IO uint32_t TimingDelay = 1000;
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
void SysTick_Handler(void)
{
  TimingDelay_Decrement();
}

 uint32_t flag = 0;

void EXTI0_IRQHandler(void){	
	
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) && TimingDelay*2 < startDelay)
					flag = 1;
			else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) && TimingDelay >= startDelay)
					flag = 0;
			
			if(flag)
				TimingDelay *= 1.1;
			else
				TimingDelay *= 0.9;
        
			EXTI_ClearITPendingBit(EXTI_Line0);  	
}

int main(){
    ButtonInit();
    it_init();
    leds_init();
		while(1)
		{
				GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
				GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
				GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
				GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
			
				Delay(TimingDelay);
			
				GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
				GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
				GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
				GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
		};
}
