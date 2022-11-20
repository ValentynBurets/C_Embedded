#ifndef LIGHTUTILS_H
#define LIGHTUTILS_H

typedef enum {
	ALL = 0,
	RED ,
	GREEN ,
	BLUE = 3
} Color;
	
void lightsOn(Color color);
void lightsOff(Color color);

#endif
