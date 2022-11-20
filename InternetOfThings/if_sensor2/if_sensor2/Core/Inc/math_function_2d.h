#ifndef INC_MATH_FUNCTION_2D_H_
#define INC_MATH_FUNCTION_2D_H_

#include <stdio.h>
#include <stdbool.h>

struct Math2DPointStruct
{
  int16_t x;
  int16_t y;
};

typedef struct Math2DPointStruct math_2d_point_t;

struct MathFunction2DObjStruct
{
  const math_2d_point_t* objP_data_table;
  uint16_t u16_table_size;
};

typedef struct MathFunction2DObjStruct math_function_2d_obj_t;

void math_function_2d_construct(math_function_2d_obj_t* objPL_this,
  const math_2d_point_t* objPL_data, uint16_t u16L_dataSize);
int16_t math_function_2d_get_y(math_function_2d_obj_t* objPL_this, int16_t s16L_x);

#endif /* INC_MATH_FUNCTION_2D_H_ */
