/*
 * ir_sensor.c
 *
 *  Created on: Nov 20, 2021
 *      Author: yaros
 */

#include "sensors.h"

#define    DWT_CYCCNT    *(volatile unsigned long *)0xE0001004
#define    DWT_CONTROL   *(volatile unsigned long *)0xE0001000
#define    SCB_DEMCR     *(volatile unsigned long *)0xE000EDFC

int32_t delay_get_us_tick()
{
  //останавливаем счётчик
  //DWT_CONTROL &= ~DWT_CTRL_CYCCNTENA_Msk;
  return DWT_CONTROL / SystemCoreClock * 1000000;
}

void ir_sensor_init(ir_sensor_t* objPL_this, ADC_HandleTypeDef* objPL_adc)
{
  //разрешаем использовать счётчик
  SCB_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  //обнуляем значение счётного регистра
  DWT_CYCCNT  = 0;
  //запускаем счётчик
  DWT_CONTROL |= DWT_CTRL_CYCCNTENA_Msk;

  objPL_this->objP_adc = objPL_adc;
  HAL_Delay(START_DELAY);
  math_function_2d_construct(&objPL_this->obj_func, objPS_data, 11);
}

uint16_t ir_sensor_read(ir_sensor_t* objPL_this)
{
  filter_t objL_filter;
  filter_init(&objL_filter, FILTER_COUNT);
  uint16_t u16L_dist = 0;

  for (uint8_t u8L_i = 0; u8L_i < FILTER_COUNT; u8L_i++)
  {
    HAL_ADC_Start(objPL_this->objP_adc);
    HAL_ADC_PollForConversion(objPL_this->objP_adc, 0xFFFF);
    u16L_dist = filter_calc(&objL_filter, HAL_ADC_GetValue(objPL_this->objP_adc));
  }
  return ir_sensor_get_distance(objPL_this, u16L_dist);
}

uint16_t ir_sensor_get_distance(ir_sensor_t* objPL_this, uint16_t u16L_adc_val)
{
  if (u16L_adc_val >= MAX_ADC || u16L_adc_val <= MIN_ADC)
  {
    return 9999;
  }
  return math_function_2d_get_y(&objPL_this->obj_func, (int16_t)u16L_adc_val);
}

void acoustic_sensor_init(acoustic_sensor_t* objPL_this, GPIO_TypeDef *objPL_trig_port, uint16_t u16L_trig_pin, GPIO_TypeDef * objPL_echo_port, uint16_t u16L_echo_pin)
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



