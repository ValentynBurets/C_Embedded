#ifndef eeprom
#define eeprom
	
#include "main.h"
int I2C_WriteData(I2C_TypeDef* I2Cx, uint8_t data);
uint8_t I2C_ReadData(I2C_TypeDef* I2Cx);
int I2C_StartTransmission(I2C_TypeDef* I2Cx, uint8_t transmissionDirection,  uint8_t slaveAddress);
int I2C_StopTransmission(I2C_TypeDef* I2Cx);

int I2C_WriteDataToSpecificPosition(I2C_TypeDef* I2Cx, uint8_t addr[], uint8_t sizeInBytes, uint8_t data[]);
int I2C_ReadDataFromSpecificPosition(I2C_TypeDef* I2Cx, uint8_t* array, uint8_t addr[], uint8_t sizeInBytes);
#define I2C_Adress  0xA0
#define BLOCKSIZE 64
#endif
