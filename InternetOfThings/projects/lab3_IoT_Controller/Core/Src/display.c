#include "display.h"

void lcdSend(uint8_t isCommand, uint8_t data) {
	RS(isCommand==0);
	HAL_Delay(1);
	DH7(((data >> 7) & 1)==1);
	DH6(((data >> 6) & 1)==1);
	DH5(((data >> 5) & 1)==1);
	DH4(((data >> 4) & 1)==1);
	EN(1);
	HAL_Delay (1);
	EN(0);
	DH7(((data >> 3) & 1)==1);
	DH6(((data >> 2) & 1)==1);
	DH5(((data >> 1) & 1)==1);
	DH4((data & 1)==1);
	EN(1);
	HAL_Delay (1);
	EN(0);
}
void lcdCommand(uint8_t cmd) {
 lcdSend(1, cmd);
}
void lcdChar(const char chr) {
 lcdSend(0, (uint8_t)chr);
}

void setCursor(uint8_t col, uint8_t row)
{
 lcdSend(1,0x80 | (col | row*0x40));
}
void parametrsToggle(uint8_t display,uint8_t cursor,uint8_t blink){
 uint8_t comm = 0x08;
 if(display)comm|=0x04;
 if(cursor)comm|=0x02;
 if(blink)comm|=0x01;
 lcdCommand(comm);
}
void shiftToggle(uint8_t rightShift,uint8_t scrollInc){
 uint8_t comm = 0x04;
 if(rightShift)comm|=0x02;
 if(scrollInc)comm|=0x01;
 lcdCommand(comm);
}
void scrollRight(void){
 lcdCommand(0x10|0x08|0x00);
}
void scrollLeft(void){
 lcdCommand(0x10|0x08|0x04);
}
void clear(void)
{
 lcdCommand(0x01);
 HAL_Delay(2);
}
void home(void)
{
 lcdCommand(0x02);
 HAL_Delay(2);
}
void initLCD(void){
 RW(0);
 HAL_Delay(40);
 lcdCommand(0x02);
 HAL_Delay(1);
 lcdCommand(0x28);
 HAL_Delay(1);
 lcdCommand(0x28);
 HAL_Delay(1);
 parametrsToggle(1,0,0);
 HAL_Delay(1);
 clear();
 shiftToggle(1,0);
}

void lcdString(char* str){
 int isSet = 0;
 for(uint8_t i=0;str[i]!='\0'; i++){
	 lcdChar(str[i]);
	 if(i > 16 && !isSet){
		 setCursor(0,1);
		 isSet = 1;
	 }
 }
}

void printTextScrollable(char* text){
	setCursor(15,0);
	for(int i=0; text[i]!= '\0'; ++i) {
		lcdChar(text[i]);
		HAL_Delay(500);
		scrollRight();
		if(i == 25){
			setCursor(15,0);
		}
	}
}
