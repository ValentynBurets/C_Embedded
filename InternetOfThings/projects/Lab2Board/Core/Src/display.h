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

#include "stm32f4xx_hal.h"
void lcdString(char* str);
void initLCD(void);
