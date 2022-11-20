/*
 * Filter.c
 *
 *  Created on: Nov 20, 2021
 *      Author: yaros
 */
#include "Filter.h"



void filter_init(filter_t* objPL_this, uint8_t u8L_filter_time)
{
  objPL_this->u32_calc_value = 0;
  objPL_this->b_filter_inited = false;
  objPL_this->u8_filter_time = u8L_filter_time;
}
uint16_t filter_calc(filter_t* objPL_this, uint16_t u16L_value)
{
  if (!objPL_this->b_filter_inited)
  {
    objPL_this->u32_calc_value = u16L_value * objPL_this->u8_filter_time;
    objPL_this->b_filter_inited = true;
    return u16L_value;
  }
  objPL_this->u32_calc_value -= objPL_this->u32_calc_value / objPL_this->u8_filter_time;
  objPL_this->u32_calc_value += u16L_value;
  return (uint16_t)(objPL_this->u32_calc_value / objPL_this->u8_filter_time);
}

