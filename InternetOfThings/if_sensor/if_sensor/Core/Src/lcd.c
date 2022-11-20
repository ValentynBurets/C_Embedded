#include "delay.h"

#include "lcd.h"

#define LCD_START_DELAY_MS 40
#define LCD_HANDLE_COMMAND_TIME 1

#define LCD_CHAR_BYTES_COUNT 8

static bool lcd_add_command(lcd_obj_t* objPL_this, bool bL_is_command, uint8_t u8L_data, uint16_t u16L_handle_time);
static bool lcd_command(lcd_obj_t* objPL_this, uint8_t u8L_cmd, uint16_t u16L_delay_time);
static bool lcd_char(lcd_obj_t* objPL_this, char cL_chr);

static void* lcd_start_delay_handler(lcd_obj_t* objPL_this);
static void* lcd_idle_handler(lcd_obj_t* objPL_this);
static void* lcd_half_data_handler(lcd_obj_t* objPL_this);
static void* lcd_command_delay_handler(lcd_obj_t* objPL_this);
static void* lcd_pull_command_handler(lcd_obj_t* objPL_this);

const static uint8_t u8PS_addresses[eCustomChar_Count] = { 0x40, 0x48, 0x50, 0x58, 0x60, 0x68, 0x70, 0x78 };

void lcd_init(lcd_obj_t* objPL_this, GPIO_TypeDef* objPL_port, uint16_t u16L_dh4_pin,
	uint16_t u16L_dh5_pin, uint16_t u16L_dh6_pin, uint16_t u16L_dh7_pin, uint16_t u16L_en_pin,
	uint16_t u16L_rw_pin, uint16_t u16L_rs_pin)
{
	objPL_this->objP_port  = objPL_port;
	objPL_this->u16_rw_pin = u16L_rw_pin;
	objPL_this->u16_rs_pin = u16L_rs_pin;
	objPL_this->u16_en_pin = u16L_en_pin;

	objPL_this->u16P_data_pins[eDataPin4] = u16L_dh4_pin;
	objPL_this->u16P_data_pins[eDataPin5] = u16L_dh5_pin;
	objPL_this->u16P_data_pins[eDataPin6] = u16L_dh6_pin;
	objPL_this->u16P_data_pins[eDataPin7] = u16L_dh7_pin;

	// Where to write
	objPL_this->u8_queue_head     = 0;
	// Where to read
	objPL_this->u8_queue_tail     = 0;
	objPL_this->u8_queue_capacity = 0;

	objPL_this->objP_handler = lcd_start_delay_handler;
	objPL_this->objP_handle_command = NULL;
	objPL_this->u16_time = delay_get_ms_tick();

	lcd_command(objPL_this, 0x02, 1);
	lcd_command(objPL_this, 0x28, 1);
	lcd_command(objPL_this, 0x28, 1);
	lcd_parametrs_toggle(objPL_this, 1,0,0);
	lcd_clear(objPL_this);
	lcd_shift_toggle(objPL_this, 1,0);
}

bool lcd_add_command(lcd_obj_t* objPL_this, bool bL_is_command, uint8_t u8L_data, uint16_t u16L_handle_time)
{
	if (objPL_this->u8_queue_capacity == QUEUE_SIZE)
	{
		return false;
	}

	uint8_t u8L_i = objPL_this->u8_queue_head;

	lcd_command_obj_t* objPL_command = &objPL_this->objP_data_queue[u8L_i];

	objPL_command->b_is_command    = bL_is_command;
	objPL_command->u16_haldle_time = u16L_handle_time;
	objPL_command->u8_command      = u8L_data;

	objPL_this->u8_queue_head = (objPL_this->u8_queue_head + 1) % QUEUE_SIZE;
	objPL_this->u8_queue_capacity++;
	return true;
}

void* lcd_start_delay_handler(lcd_obj_t* objPL_this)
{
	if (delay_get_ms_tick() - objPL_this->u16_time > LCD_START_DELAY_MS)
	{
		return lcd_idle_handler;
	}

	return lcd_start_delay_handler;
}

void* lcd_idle_handler(lcd_obj_t* objPL_this)
{
	if (objPL_this->u8_queue_capacity == 0)
	{
		objPL_this->objP_handle_command = NULL;
		return lcd_idle_handler;
	}

	objPL_this->b_first_half_setted  = false;
	objPL_this->b_second_half_setted = false;

	return lcd_pull_command_handler;
}

void* lcd_pull_command_handler(lcd_obj_t* objPL_this)
{
	if (objPL_this->b_second_half_setted)
	{
		objPL_this->u16_time = delay_get_ms_tick();

		return lcd_command_delay_handler;
	}

	if (objPL_this->b_first_half_setted)
	{
		uint8_t u8L_f_handle_data = (objPL_this->objP_handle_command->u8_command) & 0xF;

		for (uint8_t u8L_i = 0; u8L_i < eDataPin_Count; u8L_i++)
		{
			uint8_t u8L_pin_state = (u8L_f_handle_data >> u8L_i) & 1;
			HAL_GPIO_WritePin(objPL_this->objP_port, objPL_this->u16P_data_pins[u8L_i],
				u8L_pin_state ? GPIO_PIN_SET : GPIO_PIN_RESET);
		}

		HAL_GPIO_WritePin(objPL_this->objP_port, objPL_this->u16_en_pin, GPIO_PIN_SET);

		objPL_this->b_second_half_setted = true;
		objPL_this->u16_time = delay_get_ms_tick();

		return lcd_half_data_handler;
	}

	uint8_t u8L_i = objPL_this->u8_queue_tail;
	objPL_this->objP_handle_command = &objPL_this->objP_data_queue[u8L_i];

	uint8_t u8L_handle_data = (objPL_this->objP_handle_command->u8_command >> 4) & 0xF;

	if (objPL_this->objP_handle_command->b_is_command)
	{
		HAL_GPIO_WritePin(objPL_this->objP_port, objPL_this->u16_rs_pin, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(objPL_this->objP_port, objPL_this->u16_rs_pin, GPIO_PIN_SET);
	}


	for (uint8_t u8L_i = eDataPin4; u8L_i < eDataPin_Count; u8L_i++)
	{
		uint8_t u8L_pin_state = (u8L_handle_data >> u8L_i) & 1;
		HAL_GPIO_WritePin(objPL_this->objP_port, objPL_this->u16P_data_pins[u8L_i],
			u8L_pin_state ? GPIO_PIN_SET : GPIO_PIN_RESET);
	}

	HAL_GPIO_WritePin(objPL_this->objP_port, objPL_this->u16_en_pin, GPIO_PIN_SET);

	objPL_this->u16_time = delay_get_ms_tick();

	objPL_this->b_first_half_setted = true;

	return lcd_half_data_handler;
}

void* lcd_half_data_handler(lcd_obj_t* objPL_this)
{
	uint16_t u16L_crnt_time = delay_get_ms_tick();
	if (u16L_crnt_time - objPL_this->u16_time > LCD_HANDLE_COMMAND_TIME)
	{
		HAL_GPIO_WritePin(objPL_this->objP_port, objPL_this->u16_en_pin, GPIO_PIN_RESET);
		return lcd_pull_command_handler;
	}

	return lcd_half_data_handler;
}

void* lcd_command_delay_handler(lcd_obj_t* objPL_this)
{
	uint16_t u16L_crnt_time = delay_get_ms_tick();
	if (u16L_crnt_time - objPL_this->u16_time > objPL_this->objP_handle_command->u16_haldle_time)
	{
		objPL_this->u8_queue_tail = (objPL_this->u8_queue_tail + 1) % QUEUE_SIZE;
		objPL_this->u8_queue_capacity--;
		return lcd_idle_handler;
	}

	return lcd_command_delay_handler;
}

void lcd_run(lcd_obj_t* objPL_this)
{
	if (objPL_this->objP_handler != 0)
	{
		objPL_this->objP_handler = objPL_this->objP_handler(objPL_this);
	}
}

bool lcd_command(lcd_obj_t* objPL_this, uint8_t u8L_cmd, uint16_t u16L_delay_time)
{
	return lcd_add_command(objPL_this, true, u8L_cmd, u16L_delay_time);
}

bool lcd_char(lcd_obj_t* objPL_this, char cL_chr)
{
	return lcd_add_command(objPL_this, false, (uint8_t)cL_chr, 1);
}

bool lcd_home(lcd_obj_t* objPL_this)
{
	return lcd_command(objPL_this, 0x02, 2);
}

bool lcd_clear(lcd_obj_t* objPL_this)
{
	return lcd_command(objPL_this, 0x01, 2);
}
bool lcd_scroll_left(lcd_obj_t* objPL_this)
{
	return lcd_command(objPL_this, 0x10|0x08|0x04, 1);
}

bool lcd_scroll_right(lcd_obj_t* objPL_this)
{
	return lcd_command(objPL_this, 0x10|0x08|0x00, 1);
}

bool lcd_shift_toggle(lcd_obj_t* objPL_this, uint8_t u8L_right_shift, uint8_t u8L_scroll_inc)
{
	uint8_t u8L_comm = 0x04;
	if (u8L_right_shift) u8L_comm|=0x02;
	if (u8L_scroll_inc) u8L_comm|=0x01;
	return lcd_command(objPL_this, u8L_comm, 1);
}

bool lcd_parametrs_toggle(lcd_obj_t* objPL_this, uint8_t u8L_display, uint8_t u8L_cursor, uint8_t u8L_blink)
{
	uint8_t u8L_comm = 0x04;
	if (u8L_display) u8L_comm|=0x04;
	if (u8L_cursor)  u8L_comm|=0x02;
	if (u8L_blink)   u8L_comm|=0x01;
	return lcd_command(objPL_this, u8L_comm, 1);
}

bool lcd_set_cursor(lcd_obj_t* objPL_this, uint8_t u8L_col, uint8_t u8L_row)
{
	return lcd_command(objPL_this, 0x80 | (u8L_col | u8L_row*0x2), 1);
}

bool lcd_write_string(lcd_obj_t* objPL_this, const char* cPL_str)
{
	for (uint8_t u8L_i = 0; cPL_str[u8L_i]!='\0'; u8L_i++)
	{
		if (!lcd_char(objPL_this, cPL_str[u8L_i]))
		{
			return false;
		}
	}
	return true;
}

bool lcd_write_custom_char(lcd_obj_t* objPL_this, uint8_t u8L_castom_char)
{
	if (u8L_castom_char >= eCustomChar_Count)
	{
		return false;
	}

	return lcd_command(objPL_this, u8L_castom_char, 1);
}

bool lcd_create_custom_char(lcd_obj_t* objPL_this, uint8_t u8L_castom_char, uint8_t* u8PL_char_pic, uint8_t u8L_size)
{
	if (u8L_size == LCD_CHAR_BYTES_COUNT)
	{
		lcd_command(objPL_this, u8PS_addresses[u8L_castom_char], 1);
		for (uint8_t u8L_i = 0; u8L_i < LCD_CHAR_BYTES_COUNT; u8L_i++)
		{
			lcd_char(objPL_this, u8PL_char_pic[u8L_i]);
		}

		return true;
	}

	return false;
}


