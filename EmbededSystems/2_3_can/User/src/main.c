#include "stm32f4xx.h"
#include "main.h"

#include <stm32f4xx_rcc.h>   
#include <stm32f4xx_gpio.h>  
#include <misc.h>   
#include <stm32f4xx_syscfg.h>

static __IO uint32_t isSendDataToCan = 0;
static __IO uint32_t isGetDataFromCan = 0;
 
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

void EXTI0_IRQHandler(void){
	Delay(20);
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)){
		isSendDataToCan = 1;
	}
	EXTI_ClearITPendingBit(EXTI_Line0);  	
}

void CAN1_RX0_IRQHandler(void){
	isGetDataFromCan = 1;	
}

int main(){
	SystemInit();
	SysTick_Config(SystemCoreClock/1000);
	CAN1_Config();
	
	ButtonInit();
  it_init();
	
	const int size= 17;
	uint32_t id = 0x10;
	uint8_t data[] = {0x56, 0x61, 0x6c, 0x65, 0x6e, 0x74, 0x79, 0x6e, 0x20, 0x42, 0x75, 0x72, 0x65, 0x74, 0x73};
	
	int res = 0;
	while(1)
	{
		int status = 0;
		
		if(isSendDataToCan == 1){
			status = sendDataToCan(id, data, size);
			isSendDataToCan = 0;
		}
		else{
		}
		if(isGetDataFromCan == 1){
			status = receiveDataFromCan(id, data, size);
			
			isGetDataFromCan = 0;
		}			
		else{
		}		
		if(status !=0){
			res = -1;
			break;
		}		
		else{
		}
	};
	
	return res;
}
