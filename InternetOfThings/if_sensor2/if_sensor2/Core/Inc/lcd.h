/*
 * led.h
 *
 *  Created on: Oct 12, 2021
 *      Author: Sigma
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f4xx_hal.h"

#define lcdPort  GPIOE
#define rsPin  GPIO_PIN_7
#define rwPin  GPIO_PIN_10
#define enPin  GPIO_PIN_11
#define dh4Pin  GPIO_PIN_12
#define dh5Pin  GPIO_PIN_13
#define dh6Pin  GPIO_PIN_14
#define dh7Pin  GPIO_PIN_15

#define RS(X) HAL_GPIO_WritePin(lcdPort, rsPin, (X))
#define RW(X) HAL_GPIO_WritePin(lcdPort, rwPin, (X))
#define EN(X) HAL_GPIO_WritePin(lcdPort, enPin, (X))
#define DH4(X) HAL_GPIO_WritePin(lcdPort, dh4Pin, (X))
#define DH5(X) HAL_GPIO_WritePin(lcdPort, dh5Pin, (X))
#define DH6(X) HAL_GPIO_WritePin(lcdPort, dh6Pin, (X))
#define DH7(X) HAL_GPIO_WritePin(lcdPort, dh7Pin, (X))

void lcdSend(uint8_t isCommand, uint8_t data);
void lcdCommand(uint8_t cmd);
void lcdChar(const char chr);
void home(void);
void clear(void);
void scrollLeft(void);
void scrollRight(void);
void shiftToggle(uint8_t rightShift,uint8_t scrollInc);
void parametrsToggle(uint8_t display,uint8_t cursor,uint8_t blink);
void setCursor(uint8_t col, uint8_t row);
void lcdString(char* str);
void initLCD(void);

#endif /* INC_LCD_H_ */
