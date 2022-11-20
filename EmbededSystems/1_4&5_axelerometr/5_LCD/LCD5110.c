#include <stm32f407xx.h>
#include "LCD5110.h"
#include "LCDInit.h"



void LCD5110_Set_Pos(uint8_t X, uint8_t Y)
{
	LCD5110_Write_Byte(0x40 | Y, 0);
	LCD5110_Write_Byte(0x80 | X, 0);
}

void LCD5110_Set_XY(uint8_t X, uint8_t Y)
{
	LCD5110_Write_Byte(0x40 | Y, 0);
	LCD5110_Write_Byte(0x80 | (X*6), 0);
}


void LCD5110_Write_Byte(uint8_t dat, uint8_t mode)
{
	LCD5110_CS(OFF);
	
	if (!mode)
		LCD5110_DC(OFF);
	else
		LCD5110_DC(ON);
	
	for (uint8_t i = 0; i < 8; ++i)
	{
		LCD5110_MOSI(dat & 0x80);//SPI_MO = dat & 0x80;
		dat <<= 1;
		LCD5110_SCK(OFF);//SPI_SCK = 0;
		LCD5110_SCK(ON);//SPI_SCK = 1;
	}
	
	LCD5110_CS(ON);
}

void LCD5110_Clear(void)
{
	for (uint8_t i = 0; i < H; ++i)
		for (uint8_t j = 0; j < W; ++j)
			LCD5110_Write_Byte(0, 1);
}

void LCD5110_Write_Data(uint8_t *map[][W])
{
	for (uint8_t i = 0; i < H; ++i)
		for (uint8_t j = 0; j < W; ++j)
			LCD5110_Write_Byte(*map[i][j], 1);
}

