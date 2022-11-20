#ifndef DRIVER_I2C_H
#define DRIVER_I2C_H

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "delay.h"

#define BUS_SPEED 100000
#define EEPROM_I2C_ADDR  0x56           	// eeprom 7-bit I2C address
#define EEPROMMASK				0xA0
#define WAIT_TIME 				20			//<-- secure wait
#define WRBLOCKSIZ 				32			
#define WRBLOCKMSK            	(word) (0 - WRBLOCKSIZ)


void I2C_Congfig(void);
void I2C_EEPROM_ByteWrite(uint8_t HW_address, uint8_t addr, uint8_t data);
uint8_t I2C_EEPROM_ByteRead(uint8_t HW_address, uint8_t addr);
void I2C_EEPROM_BlockRead(uint8_t HW_address, uint8_t addr, uint8_t n_data, uint8_t *data);
void I2C_EEPROM_BlockWrite(uint8_t HW_address, uint8_t addr, uint8_t n_data, uint8_t *data);

#endif
