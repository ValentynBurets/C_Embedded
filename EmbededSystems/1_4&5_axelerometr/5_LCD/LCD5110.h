#ifndef LCD5110_H
#define LCD5110_H

#include <stdint.h>

#define H 12
#define W 64

void LCD5110_Write_Byte(uint8_t dat, uint8_t mode);
void LCD5110_Clear(void);
void LCD5110_Set_Pos(uint8_t X, uint8_t Y);
void LCD5110_Set_XY(uint8_t X, uint8_t Y);
void LCD5110_Write_Data(uint8_t *map[][W]);

#endif
