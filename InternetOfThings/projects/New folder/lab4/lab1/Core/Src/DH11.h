#include "stdint.h"
#include "main.h"

#define DHT11_PORT GPIOD
#define DHT11_PIN GPIO_PIN_11

uint8_t RHI, RHD, TCI, TCD, SUM;
uint32_t pMillis, cMillis;

void microDelay (uint16_t delay, TIM_HandleTypeDef htim1);
uint8_t DHT11_Start (TIM_HandleTypeDef htim1);
uint8_t DHT11_Read (TIM_HandleTypeDef htim1);
char DHT11_GetData(TIM_HandleTypeDef htim1, float* data);
