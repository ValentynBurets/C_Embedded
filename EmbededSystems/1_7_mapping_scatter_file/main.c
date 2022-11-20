#include "stm32f4xx.h"                  // Deviceheader
#include "Unicode.h"

#define  ADDRESS				 0x08010000

#ifdef COMPILE_UNICODE_GRAPHIC
extern ICON_PARAMS_T  Icon_params; 	
#else
ICON_PARAMS_T  Icon_params;
#endif

extern const unsigned char UNICODE_ID[16];

const const unsigned char FIRMWARE_ID[16]   = {'L','A','B','7',' ','M','E','M','O','R','Y',' ','M','A','P',0x00}; 
int main ()
{
unsigned char my_buff[16] = {0};
	
	my_buff[0] = UNICODE_ID[0];
	while (1);
}
