#ifndef INC_MATHFUNCTIONS2D_H_
#define INC_MATHFUNCTIONS2D_H_

#include <stdint.h>

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

static int16_t math_function_get_fx(int16_t s16L_x, int16_t s16L_x1, int16_t s16L_y1, int16_t s16L_x2, int16_t s16L_y2);
void math_function_2d_construct(math_function_2d_obj_t* objPL_this, const math_2d_point_t* objPL_data, uint16_t u16L_dataSize);
int16_t math_function_2d_get_y(math_function_2d_obj_t* objPL_this, int16_t s16L_x);
int16_t math_function_get_fx(int16_t s16L_x, int16_t s16L_x1, int16_t s16L_y1, int16_t s16L_x2, int16_t s16L_y2);

#endif /* INC_MATHFUNCTIONS2D_H_ */
