# STM32_HAL_ST7032_LCD_LIBRARY
ST7032 LCD library compatible with STM32 HAL library 
/*
 *	@File: README.MD
 *	@This lib is free to be used, modified. Headers must be remained. Thank you.
 *
 *	@Introduction: This repo is included with the library written for ST7032 LCD + example + related pics
 *  > Example is written using Eclipse + ARM GCC for Blue Pill STM32f103c8t6 and LCD MIDAS MCCOG21605B6W-BNMLWI
 *  > This library is based on STM32 HAL library. You must implement STM32 HAL library to use this library
 *	> The library requires I2C_HandleTypeDef (Master mode) & TIM_HandleTypeDef (PWM mode) to control LCD
 *	> Some codes are based on ST7306LCD_Library from author @F. Malpartida, and can be found at URL:https://github.com/pkourany/ST7306LCD_Library
 *	@MainFunction:
 *	> Initializing ST7032 based LCD in 2 line display 5x8, inst table 1 as default
 *	> Controlling LCD cursor/blink, screen shift right/left, turn on/off, move cursor to home
 * 	> Loading custom character (8 characters)
 * 	> Sending command, char, string to LCD
 * 	> Adjust contrast, backlight levels (require 1 pin for PWM to control backlight)
 *	@Bugs/requests: please contact via email, thank you.
 *
 *  @Created on: Mar. 27, 2020
 *  @Author: AARONEE - khoahuynh
 * 	@Email: khoahuynh.ld@gmail.com
 * 	@Github: https://github.com/khoahuynhld
 */
