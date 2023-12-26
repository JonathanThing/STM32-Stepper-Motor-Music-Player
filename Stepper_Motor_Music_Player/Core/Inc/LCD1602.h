/*
 * LCD1602.h
 *
 *  Created on: Dec 26, 2023
 *      Author: Jonathan Cai
 */

#ifndef INC_LCD1602_H
#define INC_LCD1602_H

void lcd_init(void);
void lcd_send_cmd(char cmd);
void lcd_send_data(char data);
void lcd_send_string(char *str);
void lcd_put_cur(int row, int col);
void lcd_clear(void);

#endif




