#ifndef LCDINIT_H
#define LCDINIT_H

typedef enum
{
	OFF = 0,
	ON = 1
} Switch;


//LCD functions for working with registers

void LCD5110_CS(Switch sw);

//Reset
void LCD5110_RST(Switch sw);

//Data/Command select
void LCD5110_DC(Switch sw);

//Master Out Slave In
void LCD5110_MOSI(Switch sw);

//Serial Clock
void LCD5110_SCK(Switch sw);


void LCD5110_Init(void);

#endif
