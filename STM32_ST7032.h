/*
 * STM32_ST7036.h
 *
 *  Created on: Mar. 27, 2020
 *      Author: AARONEE - khoahuynh
 */

#ifndef INC_STM32_ST7032_H_
#define INC_STM32_ST7032_H_

typedef struct {
	I2C_HandleTypeDef *LCD_hi2c;				/*handle i2c using for LCD*/
	TIM_HandleTypeDef *LCD_htim_backlight;		/*handle tim (PWM) using for LCD backlight*/
	uint8_t TIM_channel_backlight;				/*tim channel using for LCD backlight*/

	uint8_t num_lines;							/*number of target LCD lines*/
	uint8_t num_col;							/*number of target LCD column*/
	uint8_t i2cAddr;							/*I2C address of target LCD*/

}ST7032_InitTypeDef;
extern void LCD_ST7032_Init(ST7032_InitTypeDef *hlcd);
extern void LCD_write_byte(uint8_t value);
extern void LCD_setCursor(uint8_t line_num, uint8_t x);
extern void LCD_custom(uint8_t custom_char[8],uint8_t custom_char_location);
extern void LCD_shift(uint8_t sc_rl_s,uint8_t shift_time);
extern void LCD_contrast(uint8_t contrast);
extern void LCD_backlight(uint8_t percentage);
extern void LCD_write(const char *buffer);
extern void LCD_clear(void);
extern void LCD_home(void);
extern void LCD_on(void);
extern void LCD_off(void);
extern void LCD_cursor_on(void);
extern void LCD_cursor_off(void);
extern void LCD_blink_on(void);
extern void LCD_blink_off(void);

/** @defgroup screen_cursor_select
  * @{
  */
#define SR        0xC	// 0b1100
#define SL        0x8	// 0b1000
#define CR        0x4	// 0b0100
#define CL        0x0	// 0b0000
/**
  * @}
  */

#endif /* INC_STM32_ST7032_H_ */
