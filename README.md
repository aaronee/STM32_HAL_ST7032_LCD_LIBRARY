# STM32_HAL_ST7032_LCD_LIBRARY

	Created on: Mar. 27, 2020
	Author: AARONEE - khoahuynh
	Email: khoahuynh.ld@gmail.com
	Github: https://github.com/aaronee
  
  
## Introduction:
* Example is written using Eclipse + ARM GCC for Blue Pill STM32f103c8t6 and LCD MIDAS MCCOG21605B6W-BNMLWI
* This library is based on STM32 HAL library. You must implement STM32 HAL library to use this library
* Some codes are based on ST7306LCD_Library from author **@F. Malpartida**, and can be found at [his repo](https://github.com/pkourany/ST7306LCD_Library)
 
 
## MainFunction:
1. Initializing ST7032 based LCD in 2 line display 5x8, inst table 1 as default
1. Controlling LCD cursor/blink, screen shift right/left, turn on/off, move cursor to home
1. Send command, write to RAM function
1. Loading custom character (8 characters)
1. Adjust contrast, backlight levels (require 1 pin for PWM to control backlight)
 

