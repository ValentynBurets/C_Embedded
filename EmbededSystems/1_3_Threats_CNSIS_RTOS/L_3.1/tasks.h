#ifndef TASKS_H
#define TASKS_H

#include "osObjects.h" 
#include "cmsis_os.h"

extern osThreadId tid_redgreenLEDTask;
extern osThreadId tid_blueLEDTask;


void THREADtask_BlueLight(void const *argument);
void THREADtask_RedGreenLight(void const *argument);


#endif
