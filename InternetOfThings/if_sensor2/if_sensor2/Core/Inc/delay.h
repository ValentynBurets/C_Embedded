#ifndef INC_DELAY_H_
#define INC_DELAY_H_

#include <stdio.h>

#include <stm32f4xx_hal.h>

void delay_init(TIM_HandleTypeDef* objLP_timer);

void delay_ms(uint32_t u32L_time_ms);

void delay_us(uint32_t u32L_time_us);

uint32_t delay_get_us_tick(void);
uint32_t delay_get_ms_tick(void);

#endif /* INC_DELAY_H_ */
