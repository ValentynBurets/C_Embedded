#include "flash_write.h"

int sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	  /*!< Enable the write access to the FLASH */
  sFLASH_WriteEnable();

  /*!< Select the FLASH: Chip Select low */
  h_drv_SPI_CS_Enable();
	
	h_drv_SPI_Write_Byte(0xAD); 
	
	h_drv_SPI_CS_Disable();
	
  int status = 0;
	
	while (NumByteToWrity--){
		status = sFlash_Write_Byte(pBuffer, WriteAddr);
		
		if(status == 0){
			return 0;
		}
		
		pBuffer++;
		WriteAddr++;
	}

	return 1;
}

int sFLASH_Write_Byte(uint8_t* pBuffer, uint32_t WriteAddr)
{
  /*!< Enable the write access to the FLASH */
  sFLASH_WriteEnable();

  /*!< Select the FLASH: Chip Select low */
  h_drv_SPI_CS_Enable();

	status = sFLASH_SendByte(*pBuffer);
  if(status == 0) return 0;

  /*!< Wait the end of Flash writing */
  status = sFLASH_WaitForWriteEnd();
	if(status == 0){
		return 0;
	}
	
	/*!< Deselect the FLASH: Chip Select high */
  h_drv_SPI_CS_Disable();
	
	return 1;
}

/**
  * @brief  Polls the status of the Write In Progress (WIP) flag in the FLASH's
  *         status register and loop until write opertaion has completed.
  * @param  None
  * @retval None
  */
int sFLASH_WaitForWriteEnd(void)
{
  uint8_t flashstatus = 0;
  h_drv_SPI_CS_Enable();

  /*!< Send "Read Status Register" instruction */
  int res = sFLASH_SendByte(sFLASH_CMD_RDSR);
	if(res == 0) return 0;
	int time = timeFromStart;
  /*!< Loop as long as the memory is busy with a write cycle */
  do
  {
    /*!< Send a dummy byte to generate the clock needed by the FLASH
    and put the value of the status register in FLASH_Status variable */
    flashstatus = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
		if(timeFromStart - time > TIME_OUT){
			return 0;
		}
  }
  while ((flashstatus & sFLASH_WIP_FLAG) == SET); /* Write in progress */

  /*!< Deselect the FLASH: Chip Select high */
  h_drv_SPI_CS_Disable();
	return 1;
}

void sFLASH_WriteEnable(void)
{
   h_drv_SPI_CS_Enable();

  /*!< Send "Write Enable" instruction */
  sFLASH_SendByte(sFLASH_CMD_WREN);

  h_drv_SPI_CS_Disable();
}
