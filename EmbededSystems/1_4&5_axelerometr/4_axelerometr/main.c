#include <Driver_SPI.h>
#include <string.h>
#include "init.h"
#include "spi_func.h"
#include "stdio.h"

int main(void)
{
	init_gpio();
	init_spi();
	
	LIS_Axes axes;
	while(1)
	{
		who_am_i();
		
		//return pointer on array
		memset(&axes, 0, sizeof(LIS_Axes));
		
		LIS_Read_Axes(&axes);
	}
}
