#ifndef flash_read_h
#define flash_read_h

 #include "main.h"
 #include "init.h"
 #include "flash_memory.h"

 #define sFLASH_DUMMY_BYTE 0x00
 #define sFLASH_CMD_READ 0x0B

 int sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
 void sFLASH_StartReadSequence(uint32_t ReadAddr);
 uint8_t sFLASH_ReadByte(void);

#endif
