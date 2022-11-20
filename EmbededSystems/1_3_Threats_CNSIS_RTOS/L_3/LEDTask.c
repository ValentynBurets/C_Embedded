#include "LEDTask.h"
//#include "cmsis_os.h"
//#include "osObjects.h"  
#include "lightutils.h"

osThreadId tid_redLEDTask;
osThreadId tid_blueLEDTask;

osThreadId tid_greenLEDTask;
osThreadId tid_orangeLEDTask;


void greenLEDTask(void const *argument){
	osEvent evt;
	while(1){
		evt = osSignalWait(0x0001,osWaitForever);
		if(evt.status == osEventSignal){
			lightsOnOff(GREEN, ON);
			osDelay(1000);
			lightsOnOff(GREEN, OFF);
		}
		osThreadYield();
	}
}

void orangeLEDTask(void const *argument){
	osEvent evt;
	while(1){
		evt = osSignalWait(0x0001,osWaitForever);
		if(evt.status == osEventSignal){
			lightsOnOff(ORANGE, ON);
			osDelay(1000);
			lightsOnOff(ORANGE, OFF);
		}
		osThreadYield();
	}
}


void redLEDTask(void const *argument){
	while(1){
		lightsOnOff(RED, ON);
		osDelay(1000);
		lightsOnOff(RED, OFF);
	}
}
	

void blueLEDTask(void const *argument){
	while(1){
		lightsOnOff(BLUE, ON);
		osDelay(1000);
		lightsOnOff(BLUE, OFF);
	}
}
