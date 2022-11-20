/*
 * MathFunctions2D.c
 *
 *  Created on: Nov 20, 2021
 *      Author: yaros
 */
#include "MathFunctions2D.h"

void math_function_2d_construct(math_function_2d_obj_t* objPL_this, const math_2d_point_t* objPL_data, uint16_t u16L_dataSize)
{
  objPL_this->objP_data_table = objPL_data;
  objPL_this->u16_table_size = u16L_dataSize;
}

int16_t math_function_2d_get_y(math_function_2d_obj_t* objPL_this, int16_t s16L_x)
{
  const math_2d_point_t* objPL_first_point = &objPL_this->objP_data_table[0];
  if(s16L_x < objPL_first_point->x)
  {
    return objPL_first_point->y;
  }
  const math_2d_point_t* objPL_last_point = &objPL_this->objP_data_table[objPL_this->u16_table_size - 1];
  if (s16L_x >= objPL_last_point->x)
  {
    return objPL_last_point->y;
  }
  const math_2d_point_t* objPL_cur_point = objPL_first_point;
  const math_2d_point_t* objPL_next_point = objPL_first_point + 1;
  while (objPL_cur_point != objPL_last_point)
  {
  if (s16L_x < objPL_next_point->x)
  {
    return math_function_get_fx(s16L_x, objPL_cur_point->x, objPL_cur_point->y, objPL_next_point->x, objPL_next_point->y);
  }
  objPL_cur_point = objPL_next_point;
  objPL_next_point++;
  }
  // return 0 will never be executed
  return 0;
}

int16_t math_function_get_fx(int16_t s16L_x, int16_t s16L_x1, int16_t s16L_y1, int16_t s16L_x2, int16_t s16L_y2)
{
 return ((s16L_x - s16L_x1) * (s16L_y2 - s16L_y1)) / (s16L_x2 - s16L_x1) + s16L_y1;
}

