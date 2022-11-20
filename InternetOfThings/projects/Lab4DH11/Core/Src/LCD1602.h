/*
 * LCD1602.h
 *
 *  Created on: Nov 2, 2021
 *      Author: Valentyn
 */
#include "string.h"
#include "main.h"

#ifndef SRC_LCD1602_H_
#define SRC_LCD1602_H_


#define lcdPort GPIOE
#define rsPin GPIO_PIN_7
#define rwPin GPIO_PIN_10
#define enPin GPIO_PIN_11
#define dh4Pin GPIO_PIN_12
#define dh5Pin GPIO_PIN_13
#define dh6Pin GPIO_PIN_14
#define dh7Pin GPIO_PIN_15

#define RS(X) HAL_GPIO_WritePin(lcdPort, rsPin, (X))
#define RW(X) HAL_GPIO_WritePin(lcdPort, rwPin, (X))
#define EN(X) HAL_GPIO_WritePin(lcdPort, enPin, (X))
#define DH4(X) HAL_GPIO_WritePin(lcdPort, dh4Pin, (X))
#define DH5(X) HAL_GPIO_WritePin(lcdPort, dh5Pin, (X))
#define DH6(X) HAL_GPIO_WritePin(lcdPort, dh6Pin, (X))
#define DH7(X) HAL_GPIO_WritePin(lcdPort, dh7Pin, (X))

void lcdSend(char isCommand, char data);
void lcdCommand(char cmd);
void lcdChar(const char chr);

void setCursor(char col, char row);
void parametrsToggle(char display,char cursor,char blink);
void shiftToggle(char rightShift,char scrollInc);
void scrollRight(void);
void scrollLeft(void);
void clear(void);
void home(void);
void initLCD(void);
void lcdString(char* str);
int isIndexInBoundsOfString(char* str, int start, int end);
void lcdSubString(char* str, int start, int end);

#endif /* SRC_LCD1602_H_ */
