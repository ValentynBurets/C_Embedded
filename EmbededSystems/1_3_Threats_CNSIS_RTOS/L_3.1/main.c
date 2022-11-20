#define osObjectsPublic                     
#include "osObjects.h"                      
#include "cmsis_os.h"
#include "init.h"
#include "tasks.h"

osThreadDef(THREADtask_RedGreenLight, osPriorityNormal,1,0);
osThreadDef(THREADtask_BlueLight, osPriorityNormal,1,0);


int main (void) {
	labInit();
	
	osKernelInitialize();                    
	
	tid_redgreenLEDTask = osThreadCreate(osThread(THREADtask_RedGreenLight), NULL);
		
  osKernelStart();                        
}
