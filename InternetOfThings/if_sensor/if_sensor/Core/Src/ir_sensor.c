#include <ir_sensor.h>
#include <delay.h>

#define FILTER_COUNT 10
#define MIN_ADC 460
#define MAX_ADC 3870
#define START_DELAY 50000

static void* ir_sensor_start_dalay_handler(ir_sensor_t* objPL_this);
static void* ir_sensor_idle_handler(ir_sensor_t* objPL_this);
static void* ir_sensor_work_handler(ir_sensor_t* objPL_this);
static void* ir_sensor_wait_adc_handler(ir_sensor_t* objPL_this);

static const math_2d_point_t objPS_data[] =
{
	{ MIN_ADC,	800 },
	{ 776,  	500 },
	{ 931,  	400 },
	{ 1117, 	300 },
	{ 1365, 	250 },
	{ 1614, 	200 },
	{ 2017, 	150 },
	{ 2681, 	100 },
	{ 3413, 	80 },
	{ 3724, 	70 },
	{ MAX_ADC, 	60 }
};

void ir_sensor_init(ir_sensor_t* objPL_this, ADC_HandleTypeDef* objPL_adc)
{
	objPL_this->u16_adc_val = TOO_FAR_DIST;
	objPL_this->objP_adc    = objPL_adc;
	objPL_this->u32_timer   = delay_get_us_tick();
	objPL_this->b_on_off    = false;
	objPL_this->objP_state_handler = ir_sensor_start_dalay_handler;

	math_function_2d_construct(&objPL_this->obj_func, objPS_data, 11);
	filter_init(&objPL_this->obj_filter, FILTER_COUNT);
}

void ir_sensor_run(ir_sensor_t* objPL_this)
{
	if (objPL_this->objP_state_handler != NULL)
	{
		objPL_this->objP_state_handler = objPL_this->objP_state_handler(objPL_this);
	}
}

uint16_t ir_sensor_get_distance(ir_sensor_t* objPL_this)
{
    if (objPL_this->u16_adc_val >= MAX_ADC || objPL_this->u16_adc_val <= MIN_ADC)
	{
		return TOO_FAR_DIST;
	}

	return math_function_2d_get_y(&objPL_this->obj_func, objPL_this->u16_adc_val);
}

void* ir_sensor_idle_handler(ir_sensor_t* objPL_this)
{
	return objPL_this->b_on_off ? ir_sensor_work_handler : ir_sensor_idle_handler;
}

void* ir_sensor_start_dalay_handler(ir_sensor_t* objPL_this)
{
	if (delay_get_us_tick() - objPL_this->u32_timer > START_DELAY)
	{
		return objPL_this->b_on_off ? ir_sensor_work_handler : ir_sensor_idle_handler;
	}

	return ir_sensor_start_dalay_handler;
}

void ir_sensor_start(ir_sensor_t* objPL_this)
{
	objPL_this->b_on_off = true;
}

void ir_sensor_stop(ir_sensor_t* objPL_this)
{
	objPL_this->b_on_off = false;
}

void* ir_sensor_work_handler(ir_sensor_t* objPL_this)
{
	if (!objPL_this->b_on_off)
	{
		return ir_sensor_idle_handler;
	}

	HAL_ADC_Start_IT(objPL_this->objP_adc);
	return ir_sensor_wait_adc_handler;
}

void* ir_sensor_wait_adc_handler(ir_sensor_t* objPL_this)
{
	if ((HAL_ADC_GetState(objPL_this->objP_adc) & HAL_ADC_STATE_READY) == HAL_ADC_STATE_READY)
	{
		uint16_t u16L_adc_val = HAL_ADC_GetValue(objPL_this->objP_adc);
		objPL_this->u16_adc_val = filter_calc(&objPL_this->obj_filter, u16L_adc_val);

		ir_sensor_stop(objPL_this);
		return ir_sensor_idle_handler;
	}

	return ir_sensor_wait_adc_handler;
}
