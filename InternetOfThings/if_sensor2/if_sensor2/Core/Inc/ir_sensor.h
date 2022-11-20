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
	math_function_2d_obj_t obj_func;
};

#define TOO_FAR_DIST 1000

void ir_sensor_init(ir_sensor_t* objPL_this, ADC_HandleTypeDef* objPL_adc);

uint16_t ir_sensor_read(ir_sensor_t* objPL_this);

#endif /* INC_IR_SENSOR_H_ */
