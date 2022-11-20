#include "acoustic_sensor.h"

#define TRIG_TIME 10

static uint16_t acoustic_sensor_convert_duration(uint32_t u32L_duration);

static void* acoustic_sensor_idle_handler(acoustic_sensor_t* objPL_this);
static void* acoustic_sensor_trig_start_handler(acoustic_sensor_t* objPL_this);
static void* acoustic_sensor_trig_handler(acoustic_sensor_t* objPL_this);
static void* acoustic_sensor_echo_start_handler(acoustic_sensor_t* objPL_this);
static void* acoustic_sensor_echo_handler(acoustic_sensor_t* objPL_this);

void acoustic_sensor_init(acoustic_sensor_t* objPL_this, GPIO_TypeDef * objPL_trig_port,
	uint16_t u16L_trig_pin, GPIO_TypeDef * objPL_echo_port, uint16_t u16L_echo_pin)
{
	objPL_this->objP_echo_port = objPL_echo_port;
	objPL_this->objP_trig_port = objPL_trig_port;
	objPL_this->u16_echo_pin = u16L_echo_pin;
	objPL_this->u16_trig_pin = u16L_trig_pin;

	objPL_this->b_on_off  = false;
	objPL_this->u16_dist  = 0xFFFF;
	objPL_this->u32_timer = 0;

	objPL_this->objP_state_handler = acoustic_sensor_idle_handler;
}

void acoustic_sensor_run(acoustic_sensor_t* objPL_this)
{
	if (objPL_this->objP_state_handler != NULL)
	{
		objPL_this->objP_state_handler = objPL_this->objP_state_handler(objPL_this);
	}
}

void acoustic_sensor_start(acoustic_sensor_t* objPL_this)
{
	objPL_this->b_on_off = true;
}

void acoustic_sensor_stop(acoustic_sensor_t* objPL_this)
{
	objPL_this->b_on_off = false;
}

uint16_t acoustic_sensor_get_distance(acoustic_sensor_t* objPL_this)
{
	return objPL_this->u16_dist;
}

void* acoustic_sensor_idle_handler(acoustic_sensor_t* objPL_this)
{
	if (objPL_this->b_on_off)
	{
		return acoustic_sensor_trig_start_handler;
	}

	return acoustic_sensor_idle_handler;
}

void* acoustic_sensor_trig_start_handler(acoustic_sensor_t* objPL_this)
{
	objPL_this->u32_timer = delay_get_us_tick();
	HAL_GPIO_WritePin(objPL_this->objP_trig_port, objPL_this->u16_trig_pin, GPIO_PIN_SET);

	return acoustic_sensor_trig_handler;
}

void* acoustic_sensor_trig_handler(acoustic_sensor_t* objPL_this)
{
	if (delay_get_us_tick() - objPL_this->u32_timer > TRIG_TIME)
	{
		HAL_GPIO_WritePin(objPL_this->objP_trig_port, objPL_this->u16_trig_pin, GPIO_PIN_RESET);
		return acoustic_sensor_echo_start_handler;
	}

	return acoustic_sensor_trig_handler;
}

void* acoustic_sensor_echo_start_handler(acoustic_sensor_t* objPL_this)
{
	uint8_t u8_pin_state = HAL_GPIO_ReadPin(objPL_this->objP_echo_port, objPL_this->u16_echo_pin);

	if (u8_pin_state)
	{
		objPL_this->u32_timer = delay_get_us_tick();
		return acoustic_sensor_echo_handler;
	}

	return acoustic_sensor_echo_start_handler;
}

void* acoustic_sensor_echo_handler(acoustic_sensor_t* objPL_this)
{
	uint8_t u8_pin_state = HAL_GPIO_ReadPin(objPL_this->objP_echo_port, objPL_this->u16_echo_pin);

	if(u8_pin_state)
	{
		return acoustic_sensor_echo_handler;
	}

	uint32_t u32L_duration = delay_get_us_tick() - objPL_this->u32_timer;

	objPL_this->u16_dist = acoustic_sensor_convert_duration(u32L_duration);

	acoustic_sensor_stop(objPL_this);

	return acoustic_sensor_idle_handler;
}

uint16_t acoustic_sensor_convert_duration(uint32_t u32L_duration)
{
	return (u32L_duration * 10) / 58;
}
