#include "delay.h"

static TIM_HandleTypeDef* objSP_delay_timer;

void delay_init(TIM_HandleTypeDef* objLP_timer)
{
	objSP_delay_timer = objLP_timer;
	HAL_TIM_Base_Start(objSP_delay_timer);
}

void delay_ms(uint32_t u32L_time_ms)
{
	for (uint32_t u32L_i = 0; u32L_i < u32L_time_ms; ++u32L_i)
	{
		delay_us(1000);
	}
}

void delay_us(uint32_t u32L_time_us)
{
	uint32_t u32_crnt_time = delay_get_us_tick();
	while (__HAL_TIM_GetCounter(objSP_delay_timer) - u32_crnt_time < u32L_time_us);
}

uint32_t delay_get_us_tick(void)
{
	return __HAL_TIM_GetCounter(objSP_delay_timer);
}

uint32_t delay_get_ms_tick(void)
{
	return HAL_GetTick();
}
