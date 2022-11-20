/*
 * Filter.h
 *
 *  Created on: Nov 20, 2021
 *      Author: yaros
 */

#ifndef INC_FILTER_H_
#define INC_FILTER_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
 uint32_t u32_calc_value;
 uint8_t u8_filter_time;
 bool b_filter_inited;
} filter_t;

void filter_init(filter_t* objPL_this, uint8_t u8L_filter_time);
uint16_t filter_calc(filter_t* objPL_this, uint16_t u16L_value);

#endif /* INC_FILTER_H_ */
