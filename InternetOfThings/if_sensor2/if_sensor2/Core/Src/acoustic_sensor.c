#include "acoustic_sensor.h"

#define TRIG_TIME 10

static uint16_t acoustic_sensor_convert_duration(uint32_t u32L_duration);

void acoustic_sensor_init(acoustic_sensor_t* objPL_this, GPIO_TypeDef * objPL_trig_port,
	uint16_t u16L_trig_pin, GPIO_TypeDef * objPL_echo_port, uint16_t u16L_echo_pin)
{
	objPL_this->objP_echo_port = objPL_echo_port;
	objPL_this->objP_trig_port = objPL_trig_port;
	objPL_this->u16_echo_pin = u16L_echo_pin;
	objPL_this->u16_trig_pin = u16L_trig_pin;
}

uint16_t acoustic_sensor_read(acoustic_sensor_t* objPL_this)
{
	uint32_t u32L_timer = delay_get_us_tick();

	HAL_GPIO_WritePin(objPL_this->objP_trig_port, objPL_this->u16_trig_pin, GPIO_PIN_SET);
	while (delay_get_us_tick() - u32L_timer < TRIG_TIME);

	HAL_GPIO_WritePin(objPL_this->objP_trig_port, objPL_this->u16_trig_pin, GPIO_PIN_RESET);
	while (HAL_GPIO_ReadPin(objPL_this->objP_echo_port, objPL_this->u16_echo_pin) == GPIO_PIN_RESET);

	u32L_timer = delay_get_us_tick();
	while (HAL_GPIO_ReadPin(objPL_this->objP_echo_port, objPL_this->u16_echo_pin) == GPIO_PIN_SET);

	uint32_t u32L_duration = delay_get_us_tick() - u32L_timer;

	return acoustic_sensor_convert_duration(u32L_duration);
}

uint16_t acoustic_sensor_convert_duration(uint32_t u32L_duration)
{
	return (u32L_duration * 10) / 58;
}
