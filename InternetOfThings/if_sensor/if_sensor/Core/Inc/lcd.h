#ifndef INC_LCD_H_
#define INC_LCD_H_

#include <stdio.h>
#include <stdbool.h>

#include <stm32f4xx_hal.h>

#define QUEUE_SIZE 50

enum
{
	eDataPin4 = 0,
	eDataPin5,
	eDataPin6,
	eDataPin7,
	eDataPin_Count
};

typedef struct
{
	bool     b_is_command;
	uint8_t  u8_command;
	uint16_t u16_haldle_time;
} lcd_command_obj_t;

typedef struct LcdObjectStruct lcd_obj_t;

typedef void*(*lcd_handler_t)(lcd_obj_t*);

enum
{
	eCustomChar1 = 0,
	eCustomChar2,
	eCustomChar3,
	eCustomChar4,
	eCustomChar5,
	eCustomChar6,
	eCustomChar7,
	eCustomChar8,
	eCustomChar_Count
};

struct LcdObjectStruct
{
	GPIO_TypeDef* objP_port;
	uint16_t u16P_data_pins[eDataPin_Count];
	uint16_t u16_en_pin;
	uint16_t u16_rw_pin;
	uint16_t u16_rs_pin;

	lcd_command_obj_t objP_data_queue[QUEUE_SIZE];
	uint8_t u8_queue_head;
	uint8_t u8_queue_tail;
	uint8_t u8_queue_capacity;

	bool b_first_half_setted;
	bool b_second_half_setted;

	lcd_handler_t objP_handler;
	lcd_command_obj_t* objP_handle_command;
	uint16_t u16_time;
};

void lcd_init(lcd_obj_t* objPL_this, GPIO_TypeDef* objPL_port, uint16_t u16L_dh4_pin,
	uint16_t u16L_dh5_pin, uint16_t u16L_dh6_pin, uint16_t u16L_dh7_pin, uint16_t u16L_en_pin,
	uint16_t u16L_rw_pin, uint16_t u16L_rs_pin);

void lcd_run(lcd_obj_t* objPL_this);

bool lcd_home(lcd_obj_t* objPL_this);
bool lcd_clear(lcd_obj_t* objPL_this);
bool lcd_scroll_left(lcd_obj_t* objPL_this);
bool lcd_scroll_right(lcd_obj_t* objPL_this);
bool lcd_shift_toggle(lcd_obj_t* objPL_this, uint8_t u8L_right_shift, uint8_t u8L_scroll_inc);
bool lcd_parametrs_toggle(lcd_obj_t* objPL_this, uint8_t u8L_display, uint8_t u8L_cursor, uint8_t u8L_blink);
bool lcd_set_cursor(lcd_obj_t* objPL_this, uint8_t u8L_col, uint8_t u8L_row);
bool lcd_write_string(lcd_obj_t* objPL_this, const char* cL_str);
bool lcd_write_custom_char(lcd_obj_t* objPL_this, uint8_t u8L_castom_char);
bool lcd_create_custom_char(lcd_obj_t* objPL_this, uint8_t u8L_castom_char, uint8_t* u8PL_char_pic, uint8_t u8L_size);


#endif /* INC_LCD_H_ */
