#include "stm32f4xx.h"
#include "main.h"

#include <stm32f4xx_rcc.h>   
#include <stm32f4xx_gpio.h>  
#include <misc.h>   
#include <stm32f4xx_syscfg.h>
#include <stdbool.h>

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
	
	while(1)
	{
		if(isSendDataToCan == 1){
			int status = sendDataToCan(id, data, size);
			
			if(status !=0){
				return -1;
			}
			else{
				isSendDataToCan = 0;
			}
		}
		if(isGetDataFromCan == 1){
			int status = receiveDataFromCan(id, data, size);
			
			if(status !=0){
				return -1;
			}
			else{
				isGetDataFromCan = 0;
			}			
		}
	};
	
	return 0;
	
		
			char ch;
	int val;
	
	switch(ch) {
	case '1':
     val = 1;
		/*15.2 */ 
	case '2':
    val = 2;
   break;
	case '3':
    val=3;
   break;
	/* 15.3  */
//	default  :
//		;
  }
	
	int x;
	bool foo;
	switch (x) {
  case 1: // Compliant
    if (foo) {
      case 2: // Noncompliant
        break;
    }
    break;
  default: // Compliant
    break;
	}
	
	bool flag = false;
	switch(flag){}	
}
