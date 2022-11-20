#ifndef INC_IR_SENSOR_H_
#define INC_IR_SENSOR_H_

#include <stdio.h>
#include <stdbool.h>

#include <stm32f4xx_hal.h>

#include <filter.h>
#include <math_function_2d.h>

typedef struct IrSensorStruct ir_sensor_t;
typedef void*(*ir_handler_t)(ir_sensor_t*);

struct IrSensorStruct
{
	ADC_HandleTypeDef* objP_adc;
	filter_t obj_filter;
	math_function_2d_obj_t obj_func;
	uint16_t u16_adc_val;
	ir_handler_t objP_state_handler;
	uint32_t u32_timer;
	bool b_on_off;
};

#define TOO_FAR_DIST 1000

void ir_sensor_init(ir_sensor_t* objPL_this, ADC_HandleTypeDef* objPL_adc);

void ir_sensor_run(ir_sensor_t* objPL_this);

void ir_sensor_start(ir_sensor_t* objPL_this);
void ir_sensor_stop(ir_sensor_t* objPL_this);

uint16_t ir_sensor_get_distance(ir_sensor_t* objPL_this);

#endif /* INC_IR_SENSOR_H_ */
