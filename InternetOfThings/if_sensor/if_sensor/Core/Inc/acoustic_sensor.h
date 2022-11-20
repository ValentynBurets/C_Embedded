#ifndef INC_ACOUSTIC_SENSOR_H_
#define INC_ACOUSTIC_SENSOR_H_

#include <stdio.h>
#include <stdbool.h>

#include <stm32f4xx_hal.h>

#include <filter.h>
#include <delay.h>

typedef struct AcousticSensorStruct acoustic_sensor_t;
typedef void*(*ac_handler_t)(acoustic_sensor_t*);

struct AcousticSensorStruct
{
	GPIO_TypeDef * objP_trig_port;
	uint16_t u16_trig_pin;
	GPIO_TypeDef * objP_echo_port;
	uint16_t u16_echo_pin;

	uint16_t u16_dist;
	ac_handler_t objP_state_handler;
	bool b_on_off;

	uint32_t u32_timer;
};

void acoustic_sensor_init(acoustic_sensor_t* objPL_this, GPIO_TypeDef * objPL_trig_port,
	uint16_t u16L_trig_pin, GPIO_TypeDef * objPL_echo_port, uint16_t u16L_echo_pin);

void acoustic_sensor_run(acoustic_sensor_t* objPL_this);

void acoustic_sensor_start(acoustic_sensor_t* objPL_this);
void acoustic_sensor_stop(acoustic_sensor_t* objPL_this);

uint16_t acoustic_sensor_get_distance(acoustic_sensor_t* objPL_this);

#endif /* INC_ACOUSTIC_SENSOR_H_ */
