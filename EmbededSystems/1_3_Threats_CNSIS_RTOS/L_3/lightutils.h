#ifndef LIGHTUTILS_H
#define LIGHTUTILS_H
#define ON 1
#define OFF 0

typedef enum {
	GREEN = 0x1000 ,
	ORANGE = 0x2000,
	RED = 0x4000,
	BLUE = 0x8000
} Color;
	
void lightsOnOff(Color color, short);

#endif
