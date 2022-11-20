#ifndef TASK_H
#define TASK_H
#include "cmsis_os.h"
#include "globalDefines.h"
static osThreadId tid_redLEDTask;
static osThreadId tid_blueLEDTask;
static osThreadId tid_greenLEDTask;

void redLEDTask(void const *);
void blueLEDTask(void const *);
void greenLEDTask(void const *);
#endif
