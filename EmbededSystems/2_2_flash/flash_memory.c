#include "flash_memory.h"

/**
  * @brief  Sends a byte through the SPI interface and return the byte received
  *         from the SPI bus.
  * @param  byte: byte to send.
  * @retval The value of the received byte.
  */
uint8_t sFLASH_SendByte(uint8_t byte)
{
	int time = timeFromStart;
  /*!< Loop while DR register in not empty */
  while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_TXE) == RESET){
		if(timeFromStart - time > TIME_OUT){
			return 0x0;
		}
	};
	
  /*!< Send byte through the SPI2 peripheral */
  SPI_I2S_SendData(sFLASH_SPI, byte);
	time = timeFromStart;
  /*!< Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET){
		if(timeFromStart - time > TIME_OUT){
			return 0x0;
		}
	};

  return SPI_I2S_ReceiveData(sFLASH_SPI);
}
