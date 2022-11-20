/*
 * ir_sensor.h
 *
 *  Created on: Nov 20, 2021
 *      Author: yaros
 */

#ifndef INC_IR_SENSOR_H_
#define INC_IR_SENSOR_H_

#include "MathFunctions2D.h"
#include "Filter.h"
#include "stm32f4xx_hal.h"

#define MIN_ADC 460
#define MAX_ADC 3870
#define START_DELAY 50
#define FILTER_COUNT 3
#define TRIG_TIME 10

static const math_2d_point_t objPS_data[] =
{
 { MIN_ADC, 800 },
 { 776, 500 },
 { 931, 400 },
 { 1117, 300 },
 { 1365, 250 },
 { 1614, 200 },
 { 2017, 150 },
 { 2681, 100 },
 { 3413, 80 },
 { 3724, 70 },
 { MAX_ADC, 60 }
};

typedef struct IrSensorStruct
{
 ADC_HandleTypeDef* objP_adc;
 math_function_2d_obj_t obj_func;
} ir_sensor_t;

typedef struct AcousticSensorStruct
{
 GPIO_TypeDef * objP_trig_port;
 uint16_t u16_trig_pin;
 GPIO_TypeDef * objP_echo_port;
 uint16_t u16_echo_pin;
} acoustic_sensor_t;

void ir_sensor_init(ir_sensor_t* objPL_this, ADC_HandleTypeDef* objPL_adc);
uint16_t ir_sensor_read(ir_sensor_t* objPL_this);
uint16_t ir_sensor_get_distance(ir_sensor_t* objPL_this, uint16_t u16L_adc_val);
void acoustic_sensor_init(acoustic_sensor_t* objPL_this, GPIO_TypeDef *objPL_trig_port, uint16_t u16L_trig_pin, GPIO_TypeDef * objPL_echo_port, uint16_t u16L_echo_pin);
uint16_t acoustic_sensor_read(acoustic_sensor_t* objPL_this);
uint16_t acoustic_sensor_convert_duration(uint32_t u32L_duration);


#endif /* INC_IR_SENSOR_H_ */
