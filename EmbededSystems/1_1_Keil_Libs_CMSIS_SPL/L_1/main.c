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
  SysTick_Config(SystemCoreClock/1000);
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER	= 0x55000000;
	GPIOD->OTYPER = 0;
	GPIOD->OSPEEDR = 0;	
	while(1){
   	GPIOD->ODR = 0x9000;
		delay_ms(500);
		GPIOD->ODR = 0x0000;	
		delay_ms(500);
	}
}
