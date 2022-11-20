#include "tasks.h"
#include "lightutils.h"
#include "osObjects.h"  
#include "cmsis_os.h"


osThreadDef(THREADtask_BlueLight, osPriorityNormal,1,0);

int32_t count;
osThreadId tid_redgreenLEDTask;
osThreadId tid_blueLEDTask;

void THREADtask_BlueLight(void const *argument) {
	int32_t evenness=count/1000;
	if(evenness%2)
		lightsOn(BLUE);
	else
		lightsOff(BLUE);
}

void THREADtask_RedGreenLight(void const *argument) {
	  lightsOn(RED);
		lightsOn(GREEN);
	for(;;) {
		count++;
		osDelay(2);
		if(count%1000==0){
			tid_blueLEDTask = osThreadCreate(osThread(THREADtask_BlueLight), NULL);
		}
		if(count>=10000)
			count=0;
	}
}


