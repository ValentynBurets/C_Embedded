#include "main.h"

int main()
{
	SystemInit();
	SysTick_Config(SystemCoreClock/1000);
	
	I2C_Congfig();
	
	const int size= 67;
	
	int addr = 0x34A; //13 * 64 + 10 = 34A  13блок + 10 байт
	
	//нижній розряд
	uint8_t lsb = addr & 0xff; // mask the lower 8 bits
	//верхній розряд
	uint8_t msb = addr >> 8;   // shift the higher 8 bits
	uint8_t addrBytes[2] = {msb, lsb};
	
	uint8_t data[size];
	
	int status = I2C_ReadDataFromSpecificPosition(I2C1, data, addrBytes, size);
	if(status ==0) return 0;
	uint8_t dataToWrite[size] = {12};
	status = I2C_WriteDataToSpecificPosition(I2C1, addrBytes, size, dataToWrite);
	if(status ==0) return 0;
}

volatile uint16_t timeFromStart = 0;
void SysTick_Handler(void){
	timeFromStart++;
}
