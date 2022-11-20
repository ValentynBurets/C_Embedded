#include "eeprom.h"
int maxVaitingTime = 11000;

//генерація стартової послідовності
//номер модуля I2C, тип передачі(від мастерад до слейва або навпаки/ читання або запис), адреса eeprom контроллера
int I2C_StartTransmission(I2C_TypeDef* I2Cx, uint8_t transmissionDirection,  uint8_t slaveAddress)
{
		int timeout = timeFromStart;
    while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY)){
			// якщо шина бізі щоб не було помилок(вічного циклу)
				if(timeFromStart - timeout > maxVaitingTime){
					return 0;
				}
		}
    I2C_GenerateSTART(I2Cx, ENABLE);

		timeout = timeFromStart;
		
		//чекаємо коли будемо мастером
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)){
			// якщо шина бізі щоб не було помилок(вічного циклу)
			if(timeFromStart - timeout > maxVaitingTime){
					return 0;
			}
		};

		// відправляю через I2Cx адресу ведучого пристрою ведучому пристрою щоб проінформувати його про співпрацю
    I2C_Send7bitAddress(I2Cx, slaveAddress, transmissionDirection);
		timeout = timeFromStart;
		
		//transmition передача даних слейву
		//Directoin прийом даних від слейва
    if(transmissionDirection== I2C_Direction_Transmitter)
    {
        while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
				{
					// якщо шина бізі щоб не було помилок(вічного циклу)
					if(timeFromStart - timeout > maxVaitingTime){
					return 0;
					}
				}
    }

    if(transmissionDirection== I2C_Direction_Receiver)
    {
        while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
				{
					// якщо шина бізі щоб не було помилок(вічного циклу)
					if(timeFromStart - timeout > maxVaitingTime){
					return 0;
					}
				}
    }
		return 1;
}
int I2C_StopTransmission(I2C_TypeDef* I2Cx){
	//спеціальний набір байтів для зупинки передачі(взаємодії)
	I2C_GenerateSTOP(I2Cx, ENABLE);
	return 1;
}

int I2C_WriteData(I2C_TypeDef* I2Cx, uint8_t data)
{
    I2C_SendData(I2Cx, data);
		int timeout = timeFromStart;
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		{
			// якщо шина бізі щоб не було помилок(вічного циклу)
					if(timeFromStart - timeout > maxVaitingTime){
					return 0;
					}
		}
		return 1;
}

uint8_t I2C_ReadData(I2C_TypeDef* I2Cx)
{
		int timeout = timeFromStart;
    uint8_t data;
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))
		{
			// якщо шина бізі щоб не було помилок(вічного циклу)
					if(timeFromStart - timeout > maxVaitingTime){
						return 0; //todo implement some value;
					}
		}
    data = I2C_ReceiveData(I2Cx);
    
    return data;
}

int I2C_WriteDataToSpecificPosition(I2C_TypeDef* I2Cx, uint8_t addr[], uint8_t sizeInBytes, uint8_t data[]){
	//генерація стартової послідовності
	int status = I2C_StartTransmission(I2C1, I2C_Direction_Transmitter, I2C_Adress);
	if(status ==0) return 0;
	
	//вісім біт зсуваю в ліво а всі інші що нулі заповнюю значенням адреси
	uint16_t adress = (addr[1] << 8) | addr[0] ;
	
	//відстань від адреси для передачі до кінця блоку
	uint8_t distanceToBlockEnd = BLOCKSIZE- adress%BLOCKSIZE;
	//відправляю спочатку на старший байт
	status = I2C_WriteData(I2C1, addr[1]);
	if(status ==0) return 0;
	//потім на молодший
	status = I2C_WriteData(I2C1, addr[0]);
	if(status ==0) return 0;
	int currentIndex= 0;

	
	while (sizeInBytes>0){
		status = I2C_WriteData(I2C1, data[currentIndex]);
		if(status ==0) return 0;
			currentIndex++;
			sizeInBytes--;
			distanceToBlockEnd--;
			adress++;
		
		//переключаємося на інший блок
		if(distanceToBlockEnd <= 0){
			I2C_StopTransmission(I2C1);
			status = I2C_StartTransmission(I2C1, I2C_Direction_Transmitter, I2C_Adress);
			uint8_t lsb = adress & 0xff; // mask the lower 8 bits
			uint8_t msb = adress >> 8;   // shift the higher 8 bits
			if(status ==0) return -1;
				status = I2C_WriteData(I2C1, msb);
			if(status ==0) return -1;
				status = I2C_WriteData(I2C1, lsb);
			if(status ==0) return -1;
				distanceToBlockEnd = 64;
			}
	}
	return 1;
}

int I2C_ReadDataFromSpecificPosition(I2C_TypeDef* I2Cx, uint8_t* array, uint8_t addr[], uint8_t sizeInBytes){
	int status = I2C_StartTransmission(I2C1,I2C_Direction_Transmitter, I2C_Adress);
	if(status ==0) return 0;
	status = I2C_WriteData(I2C1, addr[1]);
	if(status ==0) return 0;
	status = I2C_WriteData(I2C1, addr[0]);
	if(status ==0) return 0;
	I2C_StartTransmission(I2C1,I2C_Direction_Receiver, I2C_Adress);
	int currentIndex = 0;
	while(sizeInBytes>0){
		array[currentIndex] = I2C_ReadData(I2C1);
		currentIndex++;
		sizeInBytes--;
	}
	
	I2C_StopTransmission(I2C1);
	return 1;
}
