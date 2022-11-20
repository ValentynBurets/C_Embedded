#include "LCD1602.h"

void lcdSend(char isCommand, char data) {
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

void lcdCommand(char cmd) {
 lcdSend(1, cmd);
}

void lcdChar(const char chr) {
 lcdSend(0, chr);
}

void setCursor(char col, char row)
{
 lcdSend(1 , 0x80 | (col | row*0x40));
}

void parametrsToggle(char display,char cursor,char blink){
 char comm = 0x08;
 if(display)comm|=0x04;
 if(cursor)comm|=0x02;
 if(blink)comm|=0x01;
 lcdCommand(comm);
}

void shiftToggle(char rightShift, char scrollInc){
 char comm = 0x04;
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
 for(char i=0; str[i]!='\0';i++){
 lcdChar(str[i]);
 }
}

int isIndexInBoundsOfString(char* str, int start, int end){
	if(start < 0 || end < 0){
		return -1;
	}

	if((start + 1) > strlen(str) || (end + 1) > strlen(str)){
		return -1;
	}
}

void lcdSubString(char* str, int start, int end){
 if(isIndexInBoundsOfString(str, start, end) < 0){
	 return;
 }

 for(int i=start; i <= end; i++){
	 lcdChar(str[i]);
 }
}



