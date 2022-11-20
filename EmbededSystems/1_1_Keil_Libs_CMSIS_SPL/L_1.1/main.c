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
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; //port A
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; //port B
 
GPIOA->MODER = 0x00040000; 
GPIOC->MODER = 0x00000410; 
 
GPIOA->OTYPER = 0; 
GPIOA->OTYPER = 0; 
GPIOC->OSPEEDR = 0; 
GPIOC->OSPEEDR = 0; 

GPIOA->ODR = 0x00000080; 	//7
GPIOB->ODR = 0x00004800;  //11, 14

}

//int main (void){
//  SysTick_Config(SystemCoreClock/1000);
//	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; //turn on timing
//	
//	GPIOD->MODER	= 0x55000000; // port configuration
//	GPIOD->OTYPER = 0;  
//	GPIOD->OSPEEDR = 0;	
//	while(1){
//   	GPIOD->ODR = 0xC000;
//		delay_ms(1000);
//		GPIOD->ODR = 0x3000;	
//		delay_ms(1000);
//	}
//}
