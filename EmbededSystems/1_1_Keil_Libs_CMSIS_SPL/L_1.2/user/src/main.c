#include "stm32f4xx.h"                  // Device header


RCC_ClocksTypeDef RCC_Clocks;
static __IO uint32_t TimingDelay;
 
void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

void TimingDelay_Decrement(void){
  if (TimingDelay != 0x00){ 
    TimingDelay--;
  }
}
void SysTick_Handler(void)
{
  TimingDelay_Decrement();
}

int main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init( GPIOC, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
	
	while(1){
			GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
			GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
	
			Delay(1000);
			
			GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
			GPIO_ToggleBits(GPIOD, GPIO_Pin_14);		
			
			GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
	
			Delay(1000);
			
			GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
	
	}	

}
