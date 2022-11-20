#include <Driver_SPI.h>
#include <stm32f407xx.h>
#include "init.h"
#include "spi_func.h"

typedef enum
{
	OFF,
	ON
} CS_Status;

static void CS_OnOff(CS_Status stat)
{
	switch(stat)
	{
	case ON:
		GPIOE->ODR &= ~GPIO_ODR_ODR_3;
		break;
	case OFF:
		GPIOE->ODR |= GPIO_ODR_ODR_3;
		break;
	}
}

int32_t SPI_Read(uint16_t reg, int16_t *val)
{
	ARM_DRIVER_SPI *SPIdrv = &Driver_SPI1;
	
	//setting the unit in the high bit
	CS_OnOff(ON);
	reg |= 0x80;
	
	//send data witch register to use
	SPIdrv->Send(&reg, 1);
	
	//check that the register WHO_AM_I respond
	//check the register is busy
	while(SPIdrv->GetStatus().busy);
	
	//read data
	SPIdrv->Receive(val, 1);
	while(SPIdrv->GetStatus().busy);
	
	//unsetting the unit in the high bit
	CS_OnOff(OFF);
	return 0;
}

int32_t SPI_Write(uint16_t reg, int16_t val)
{
	ARM_DRIVER_SPI *SPIdrv = &Driver_SPI1;
	
	int16_t data[2];
	data[0] = reg;
	data[1] = val;
	
	CS_OnOff(ON);
	SPIdrv->Send(data, 2);
	while(SPIdrv->GetStatus().busy);
	
	if(SPIdrv->GetDataCount() != 2)
		return -1;
	CS_OnOff(OFF);
	
	return 0;
	
}


void LIS_Read_Axes(LIS_Axes *axes)
{
	int16_t data[6] = {0};
	
	for(uint8_t i = 0; i < 6; ++i)
	{
		//SPI_Write(LIS3DSH_OUT_X_L + i, i);
		SPI_Read(LIS3DSH_OUT_X_L + i,&data[i]);
	}
	
	axes->X = (int16_t)(((data[1] << 8) + data[0]) * 0.06);
	axes->Y = (int16_t)(((data[3] << 8) + data[2]) * 0.06);
	axes->Z = (int16_t)(((data[5] << 8) + data[4]) * 0.06);
}

int16_t who_am_i(void)
{
	int16_t val = 0;
	SPI_Read(WHO_AM_I, &val);
	return val;
}
