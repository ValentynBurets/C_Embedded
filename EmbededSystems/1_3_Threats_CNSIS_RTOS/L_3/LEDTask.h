#ifndef TASK_H
#define TASK_H

#include "cmsis_os.h"

extern osThreadId tid_redLEDTask;
extern osThreadId tid_blueLEDTask;
extern osThreadId tid_greenLEDTask;
extern osThreadId tid_orangeLEDTask;

void greenLEDTask(void const *argument);
void orangeLEDTask(void const *argument);
void redLEDTask(void const *argument);
void blueLEDTask(void const *argument);

#endif

//#ifndef TASKS_H
//#define TASKS_H

//#include "osObjects.h" 
//#include "cmsis_os.h"

//extern osThreadId tid_redgreenLEDTask;
//extern osThreadId tid_blueLEDTask;


//void THREADtask_BlueLight(void const *argument);
//void THREADtask_RedGreenLight(void const *argument);


//#endif

