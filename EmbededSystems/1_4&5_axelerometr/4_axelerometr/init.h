#ifndef INIT_GPIO
#define INIT_GPIO

#include <Driver_SPI.h>
extern ARM_DRIVER_SPI Driver_SPI1;

void init_gpio(void);
short init_spi(void);

#endif
