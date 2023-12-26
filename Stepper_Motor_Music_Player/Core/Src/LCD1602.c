/*
 * LCD1602.c
 *
 *  Created on: Dec 26, 2023
 *      Author: Jonathan Cai
 */

#include <LCD1602.h>
#include "stm32f1xx_hal.h"

#define RS_PORT GPIOB
#define RS_PIN GPIO_PIN_12
#define RW_PORT GPIOB
#define RW_PIN GPIO_PIN_13
#define EN_PORT GPIOB
#define EN_PIN GPIO_PIN_14
#define D4_PORT GPIOB
#define D4_PIN GPIO_PIN_3
#define D5_PORT GPIOB
#define D5_PIN GPIO_PIN_4
#define D6_PORT GPIOB
#define D6_PIN GPIO_PIN_5
#define D7_PORT GPIOB
#define D7_PIN GPIO_PIN_6

void send_to_lcd(char data, int rs)
{
	HAL_GPIO_WritePin(RS_GPIO_PORT, RS_PIN, rs);

	HAL_GPIO_WritePin(D7_GPIO_PORT, D7_PIN, (data>>3)&0x01);
	HAL_GPIO_WritePin(D6_GPIO_PORT, D6_PIN, (data>>2)&0x01);
	HAL_GPIO_WritePin(D5_GPIO_PORT, D5_PIN, (data>>1)&0x01);
	HAL_GPIO_WritePin(D4_GPIO_PORT, D4_PIN, (data>>0)&0x01);

	HAL_GPIO_WritePin(EN_GPIO_PORT, EN_PIN, 1);
	HAL_GPIO_WritePin(EN_GPIO_PORT, EN_PIN, 0);
}


void lcd_send_cmd(char cmd)
{
	char dataToSend;
	// Send upper nibble
	dataToSend = (cmd>>4)&0x0f;
	send_to_lcd(dataToSend, 0);

	// Send lower nibble
	dataToSend = cmd&0x0f;
	send_to_lcd(dataToSend, 0);
}


void lcd_send_data(char data)
{
	char dataToSend;
	// Send upper nibble
	dataToSend = (data>>4)&0x0f;
	send_to_lcd(dataToSend, 1);

	// Send lower nibble
	dataToSend = data&0x0f;
	send_to_lcd(dataToSend, 1);
}


void lcd_clear(void)
{
	lcd_send_cmd(0x01);
	HAL_Delay(2);
}

void lcd_put_cur(int row, int col)
{
	switch (row)
	{
		case 0:
			col |= 0x80;
			break;
		case 1:
			col |= 0xC0;
			break;
	}

	lcd_send_cmd(col);
}

void lcd_init(void)
{
	HAL_Delay(50);
	lcd_send_cmd(0x30);
	HAL_Delay(5);
	lcd_send_cmd(0x30);
	HAL_Delay(1);
	lcd_send_cmd(0x30);
	HAL_Delay(10);
	lcd_send_cmd(0x20);
	HAL_Delay(10);

    lcd_send_cmd (0x28);
    HAL_Delay(1);
    lcd_send_cmd (0x08);
    HAL_Delay(1);
    lcd_send_cmd (0x01);
    HAL_Delay(1);
    HAL_Delay(1);
    lcd_send_cmd (0x06);
    HAL_Delay(1);
    lcd_send_cmd (0x0C);
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}
