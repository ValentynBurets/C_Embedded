#include "task.h"

osThreadDef(redLEDTask, osPriorityNormal,1,0);
osThreadDef(blueLEDTask, osPriorityNormal,1,0);
osThreadDef(greenLEDTask, osPriorityNormal,1,0);

int main (void) 
{
	ConfigGPIO();
	ConfigEXTI();
	osKernelInitialize();
	tid_redLEDTask = osThreadCreate(osThread(redLEDTask), NULL);
	tid_blueLEDTask = osThreadCreate(osThread(blueLEDTask), NULL);
	tid_greenLEDTask = osThreadCreate(osThread(greenLEDTask), NULL);
  osKernelStart();                        
}
