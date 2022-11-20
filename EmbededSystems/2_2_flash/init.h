#ifndef inith
#define inith

	#include "main.h"

	void h_drv_SPI_Initialization (void);
	/*Керування лінією CS (CE) для деактивації пам'яті */
	void h_drv_SPI_CS_Disable (void);

	/*Керування лінією CS (CE) для активації пам'яті */
	void h_drv_SPI_CS_Enable (void);
	
#endif
