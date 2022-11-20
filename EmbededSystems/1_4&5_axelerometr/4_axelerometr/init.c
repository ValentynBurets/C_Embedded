#include <stm32f407xx.h>
#include <stdlib.h>

#include "init.h"

extern ARM_DRIVER_SPI Driver_SPI1;

void init_gpio(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOEEN;
	
	GPIOA->MODER |= GPIO_MODER_MODER5_1 | GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_1 | GPIO_OSPEEDER_OSPEEDR6_1 | GPIO_OSPEEDER_OSPEEDR7_1;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD5_1 | GPIO_PUPDR_PUPD6_1 | GPIO_PUPDR_PUPD7_1; 
	
	GPIOE->MODER |= GPIO_MODER_MODER3_0;
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3_1;
	GPIOE->PUPDR |= GPIO_PUPDR_PUPD3_1;
}

short init_spi()
{	
	RCC->AHB2ENR |= RCC_APB2ENR_SPI1EN;
	
	//create struct arm driver spi
	ARM_DRIVER_SPI *SPIdrv = &Driver_SPI1;
	
	SPIdrv->Initialize(NULL);
	
	SPIdrv->PowerControl(ARM_POWER_FULL);
	
	//SPI operating mode
	//SPI Bit Order From MSB to LSB
	//An SPI master does not drive or monitor the SS line. For example, when connecting to a single slave, the SS line can be connected to a fixed low level.
	//data length
	SPIdrv->Control(ARM_SPI_MODE_MASTER 
		| ARM_SPI_CPOL1_CPHA1 
		| ARM_SPI_MSB_LSB 
		| ARM_SPI_SS_MASTER_UNUSED
		| ARM_SPI_DATA_BITS(8), 10000);
	
	return 0;
}

