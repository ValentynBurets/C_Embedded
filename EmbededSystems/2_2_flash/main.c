#include "stm32f4xx_gpio.h"
#include <stm32f4xx.h> 

uint16_t delay_c = 0; 
void SysTick_Handler(void){
	if(delay_c > 0)
		delay_c--;
}
void delay_ms(uint16_t delay_t){
	delay_c = delay_t;
	while(delay_c){};
}
int main (void){
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_PPPx, ENABLE); 
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD, GPIO_Pin_15);
}

