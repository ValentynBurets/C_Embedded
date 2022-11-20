//#include "stm32f4xx.h"
//#include "osObjects.h"  
#include "cmsis_os.h"
#include "LEDTask.h"
#include "LEDInit.h"
#include "stm32f4xx_hal_gpio.h"

#include "stm32f4xx.h"
#include "stm32f4xx_hal_cortex.h"
#include "stm32f4xx_hal.h"

 // prototypes for timer 
void TimerGreenLED_Callback (void const *arg);
void TimerOrangeLED_Callback (void const *arg);

// define timers
osTimerDef (TimerGreenLED, TimerGreenLED_Callback);
osTimerDef (TimerOrangeLED, TimerOrangeLED_Callback);

//create
osThreadDef(redLEDTask, osPriorityNormal, 1, 0);
osThreadDef(blueLEDTask, osPriorityNormal, 1, 0);

osThreadDef(greenLEDTask, osPriorityNormal, 1, 0);
osThreadDef(orangeLEDTask, osPriorityNormal, 1, 0);
//--------------

int main(){
	//arguments for timers
	uint32_t exec1;
	uint32_t exec2;	
	
	
	osTimerId id1;
	osTimerId id2;

	ConfigGPIO();
	ConfigEXTI();
	
	osKernelInitialize(); 
	
	exec1 = 1;
	id1 = osTimerCreate (osTimer(TimerGreenLED), osTimerPeriodic, &exec1);
	if (id1 != NULL)  {
		if(osTimerStart(id1, 10) != osOK) {
			
		} 
	}
	
	exec2 = 2;
	id2 = osTimerCreate (osTimer(TimerOrangeLED), osTimerPeriodic, &exec2);
	if (id2 != NULL)  {
		if(osTimerStart(id2, 10) != osOK) {
			
		} 
	}
	// threads with timer
	tid_greenLEDTask = osThreadCreate (osThread(greenLEDTask), NULL);
	tid_orangeLEDTask = osThreadCreate (osThread(orangeLEDTask), NULL);
	//------
	
	// usual threads
	tid_redLEDTask = osThreadCreate (osThread(redLEDTask), NULL);
	tid_blueLEDTask = osThreadCreate (osThread(blueLEDTask), NULL);
	//------
	
	osKernelStart();
}

short greenLEDCounter = 0;
short orangeLEDCounter = 0;
void TimerGreenLED_Callback (void const *arg){
	if(greenLEDCounter == 500){	
		osSignalSet(tid_greenLEDTask, 1);
		greenLEDCounter = 0;
	}
	
	greenLEDCounter++;
}


void TimerOrangeLED_Callback (void const *arg){
	
	if(orangeLEDCounter == 1000)	{	
		osSignalSet(tid_orangeLEDTask, 1);
		orangeLEDCounter = 0;
	}
	
	orangeLEDCounter++;
}

