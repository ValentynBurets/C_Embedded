#ifndef flash_h
#define flash_h

	#include "stm32f4xx.h"
	#include "stm32f4xx_gpio.h"
	#include "stm32f4xx_rcc.h"
	#include "stm32f4xx_exti.h"
	#include "stm32f4xx_syscfg.h"
	#include "misc.h"
	#include "stm32f4xx.h"

	#define sFLASH_WIP_FLAG 100

	#define sFLASH_CMD_WREN 0x06
	#define sFLASH_CMD_WRITE 0x10

	#define sFLASH_SPI_PAGESIZE 4000
	#define sFLASH_SPI SPI2
	#define TIME_OUT 10000

	uint8_t sFLASH_SendByte(uint8_t byte);

	extern volatile uint16_t timeFromStart;

#endif
