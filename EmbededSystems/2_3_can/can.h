#ifndef CAN_H
#define CAN_H
	#include "stm32f4xx_can.h"
	int sendDataToCan(const uint32_t id, uint8_t* data, int sizeInBytes);
	int receiveDataFromCan(const uint32_t id, uint8_t* data, int sizeInBytes);
#endif
