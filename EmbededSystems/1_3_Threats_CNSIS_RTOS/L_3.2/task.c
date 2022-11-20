#include "task.h"


void redLEDTask(void const *argument){
	while(1){
		LEDSwitchOnOff(RED, ON);
		osDelay(1000);
	}
}
void blueLEDTask(void const *argument){
	while(1){
		LEDSwitchOnOff(BLUE, ON);
		osDelay(1000);
	}
}
void greenLEDTask(void const *argument){
	osEvent evt;
	while(1){
		evt = osSignalWait(0x0001,osWaitForever);
		if(evt.status == osEventSignal){
			LEDSwitchOnOff(GREEN, ON);
			osDelay(1000);
		}
		osThreadYield();
	}
}

void EXTI0_IRQHandler(void)
{
	osSignalSet(tid_greenLEDTask, 0x0001);
	osDelay (1000);
  EXTI->PR |= EXTI_PR_PR0;
}

