#ifndef SPI_RW
#define SPI_RW

#include <stdint.h>

#define LIS3DSH_OUT_X_L      	0x28
#define LIS3DSH_OUT_X_H      	0x29
#define LIS3DSH_OUT_Y_L      	0x2A
#define LIS3DSH_OUT_Y_H      	0x2B
#define LIS3DSH_OUT_Z_L      	0x2C
#define LIS3DSH_OUT_Z_H      	0x2D

#define WHO_AM_I							0x0F

typedef struct _LIS_Axes
{
	int16_t X;
	int16_t Y;
	int16_t Z;
} LIS_Axes;


int32_t SPI_Read(uint16_t reg, int16_t *val);
int32_t SPI_Write(uint16_t reg, int16_t val);


//func for accelerometr
void LIS_Read_Axes(LIS_Axes *axes);
int16_t who_am_i(void);


#endif
