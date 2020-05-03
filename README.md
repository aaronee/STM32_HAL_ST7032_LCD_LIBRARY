# STM32_HAL_ST7032_LCD_LIBRARY
ST7032 LCD library compatible with STM32 HAL library 

 @File: README.MD
 
 @This lib is provided as is and free to be used. Thank you.
 
  Please use the file in main folder (not in the example), as it will be the last update
  
  
 @Introduction: This repo is included with the library written for ST7032 LCD + example + related pics
 * Example is written using Eclipse + ARM GCC for Blue Pill STM32f103c8t6 and LCD MIDAS MCCOG21605B6W-BNMLWI
 * This library is based on STM32 HAL library. You must implement STM32 HAL library to use this library
 * The library requires I2C_HandleTypeDef struct & TIM_HandleTypeDef struct (optional for backlight)
 * Some codes are based on ST7306LCD_Library from author @F. Malpartida, and can be found at      URL:https://github.com/pkourany/ST7306LCD_Library
 
 
 @MainFunction:
 * Initializing ST7032 based LCD in 2 line display 5x8, inst table 1 as default
 * Controlling LCD cursor/blink, screen shift right/left, turn on/off, move cursor to home
 * Send command, write to RAM function
 * Loading custom character (8 characters)
 * Adjust contrast, backlight levels (require 1 pin for PWM to control backlight)
 
 @Bugs/requests: please contact via email, thank you.
 
 @Created on: Mar. 27, 2020
 
 @Author: AARONEE - khoahuynh
 
 @Email: khoahuynh.ld@gmail.com
 
 @Github: https://github.com/aaronee
