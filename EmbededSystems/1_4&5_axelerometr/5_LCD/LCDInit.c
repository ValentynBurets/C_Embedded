#include "LCDInit.h"
#include "LCD5110.h"
#include <stm32f407xx.h>

void LCD5110_CS(Switch sw)
{
	if (sw)
		GPIOC->ODR |= GPIO_ODR_ODR_9;
	else
		GPIOC->ODR &= ~GPIO_ODR_ODR_9;
}

void LCD5110_RST(Switch sw)
{
	if (sw)
		GPIOC->ODR |= GPIO_ODR_ODR_8;
	else
		GPIOC->ODR &= ~GPIO_ODR_ODR_8;
}

void LCD5110_DC(Switch sw)
{
	if (sw)
		GPIOC->ODR |= GPIO_ODR_ODR_7;
	else
		GPIOC->ODR &= ~GPIO_ODR_ODR_7;
}

void LCD5110_MOSI(Switch sw)
{
	if (sw)
		GPIOC->ODR |= GPIO_ODR_ODR_6;
	else
		GPIOC->ODR &= ~GPIO_ODR_ODR_6;
}

void LCD5110_SCK(Switch sw)
{
	if (sw)
		GPIOA->ODR |= GPIO_ODR_ODR_8;
	else
		GPIOA->ODR &= ~GPIO_ODR_ODR_8;
}

void LCD5110_Init(void)
{
	
	LCD5110_DC(ON);
	LCD5110_MOSI(ON);
	LCD5110_SCK(ON);
	LCD5110_CS(ON);
	
	LCD5110_RST(OFF);
	LCD5110_RST(ON);
	
	LCD5110_Write_Byte(0x21,0);
	LCD5110_Write_Byte(0xC6,0);
	LCD5110_Write_Byte(0x06,0);
	LCD5110_Write_Byte(0x13,0);
	LCD5110_Write_Byte(0x20,0);
	
	LCD5110_Clear();
	
	LCD5110_Write_Byte(0x0C,0);
}
