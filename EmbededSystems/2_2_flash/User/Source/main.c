#include "main.h"

int main(){
	SystemInit();
	SysTick_Config(SystemCoreClock/1000);
	h_drv_SPI_Initialization();
	
	int addr = 0x028A; // 10 * 64 + 10 = 28A 10блок + 10 байт 
	uint8_t data[SIZE] = {0};
	
	int status = sFLASH_ReadBuffer(data, addr, SIZE);
	
	if(status == 0){
		return -1;
	}
	
	status = sFLASH_WriteBuffer(data, addr, SIZE);
	
	if(status == 0){
		return 1;
	}	
}

volatile uint16_t timeFromStart = 0;
void SysTick_Handler(void){
	timeFromStart++;
}
