#ifndef flash_write_h
#define flash_write_h

	#include "flash_memory.h"
	#include "init.h"

	#define sFLASH_CMD_RDSR 0x05
	#define sFLASH_DUMMY_BYTE 0x00

	int sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
	int sFLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
	int sFLASH_WaitForWriteEnd(void);
	void sFLASH_WriteEnable(void);

#endif
