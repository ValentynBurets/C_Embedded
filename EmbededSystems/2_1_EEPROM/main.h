#ifndef MAIN_H
#define MAIN_H

#include <stm32f4xx.h>
#include "delay.h"
#include "Driver_I2C.h"
#include "Driver_EEPROM.h"
#include "eeprom.h"

#define CHECK_BIT(var,pos) (((var)>>(pos)) & 1)

extern volatile uint16_t timeFromStart;

#endif
