#include "Driver_I2C.h"

void I2C_Congfig(void)
{
	#pragma region initGPIO
	
	//включання тактування на шині AHB1
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	//структура для налаштування пінів
	GPIO_InitTypeDef GPIO_InitStruct;
	
	// 6 && 7 || 8 && 9 || 6 && 9
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 |GPIO_Pin_9;
	
	//сигнал піна не обробляється процесором а оброляється можулем в мікропроцеосорі в I2C
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	// Open-drain на вхід і на вихід ,, push-pull тільки на вихід
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;

	//резистор Pull up Pull down  викоритовуються для визначення 
	//визначенного статану, щоб не було не визначеного стану
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_PinAFConfig(GPIOB,
									 GPIO_PinSource8, 
									 GPIO_AF_I2C1);
  GPIO_PinAFConfig(GPIOB,
									 GPIO_PinSource9, 
									 GPIO_AF_I2C1);
	
	#pragma endregion initGPIO
	
	
	#pragma region initI2C
	
	//структура для налаштування I2C інтерфейсу
	I2C_InitTypeDef I2C_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	
	//<400 000
	I2C_InitStruct.I2C_ClockSpeed = BUS_SPEED;   
	
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;   
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2; 
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;   
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;  
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; 
	I2C_Init(I2C1, &I2C_InitStruct);
	I2C_Cmd(I2C1, ENABLE);
	
	#pragma endregion initI2C
}


