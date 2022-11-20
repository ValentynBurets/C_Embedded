#ifndef can_init_h
#define can_init_h

	#define CAN1_GPIO_CLK RCC_AHB1Periph_GPIOD
	#define CAN1_GPIO_PORT GPIOD
	#define CAN1_RX_SOURCE GPIO_Pin_1
	#define CAN1_TX_SOURCE GPIO_Pin_1

	#define CAN1_RX_PIN GPIO_Pin_1
	#define CAN1_TX_PIN GPIO_Pin_2

	#include "stm32f4xx_can.h"

	void CAN1_Config(void);
	
#endif
