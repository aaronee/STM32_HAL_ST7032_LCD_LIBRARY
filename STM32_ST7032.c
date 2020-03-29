/*
 *	@File: STM32_ST7032.c
 *	@This file is free to be used, modified. This header must be remained. Thank you.
 *
 *	@Introduction: This is the library writen for ST7032 LCD
 *				> This library is based on STM32 HAL library. You must use STM32 HAL library to use this library
 *				> The library requires I2C_HandleTypeDef (Master mode) & TIM_HandleTypeDef (PWM mode) to control LCD
 *				> Some codes are based on ST7306LCD_Library from author @F. Malpartida, and can be found at URL:https://github.com/pkourany/ST7306LCD_Library
 *	@MainFunction: 
 *				> Initializing ST7036 based LCD in 2 line display 5x8, inst table 1 as default
 *				> Controling LCD cursor/blink, screen shift right/left, turn on/off, move cursor to home
 * 				> Loading custom character (8 characters)
 * 				> Sending command, char, string to LCD
 * 				> Adjust contrast, backlight levels (require 1 pin for PWM to control backlight)
 * 					
 *  @Created on: Mar. 27, 2020
 *  @Author: AARONEE - khoahuynh
 * 	@Email: khoahuynh.ld@gmail.com
 * 	@Github: https://github.com/khoahuynhld
 */
#include "main.h"
#include "STM32_ST7032.h"
#include <stdio.h>
#include <string.h>

uint8_t LCD_buff[80];
uint8_t _initialized = 0;
ST7032_InitTypeDef _hlcd = {0};

const int	CMD_DELAY           = 1;	// Command delay in miliseconds
const int	CHAR_DELAY          = 0;	// Delay between characters in miliseconds
const int	MAX_CCHAR			= 8;	// Maximum custom character
/* LCD Command set */
const uint8_t DISP_CMD			= 0x0;	// Command for the display
const uint8_t RAM_WRITE_CMD		= 0x40; // Write to display RAM
const uint8_t CLEAR_DISP_CMD	= 0x01; // Clear display command
const uint8_t HOME_CMD			= 0x02; // Set cursor at home (0,0)
const uint8_t DISP_ON_CMD		= 0x0C; // Display on command
const uint8_t DISP_OFF_CMD		= 0x08; // Display off Command
const uint8_t SET_DDRAM_CMD		= 0x80; // Set DDRAM address command
const uint8_t CONTRAST_CMD		= 0x70; // Set contrast LCD command
const uint8_t FUNC_SET_TBL0		= 0x38; // Function set - 8 bit, 2 line display 5x8, inst table 0
const uint8_t FUNC_SET_TBL1		= 0x39; // Function set - 8 bit, 2 line display 5x8, inst table 1
const uint8_t FUNC_SET_TBL1_1L  = 0x31; // Function set - 8 bit, 1 line display 5x8, inst table 1
const uint8_t FUNC_SET_TBL1_1LH	= 0x35; // Function set - 8 bit, 2 line display 5x16, inst table 1
const uint8_t DISP_SHIFT_CMD	= 0x10; // Cursor - Display shift command

/* LCD bitmap definition */
const uint8_t CURSOR_ON_BIT  = ( 1 << 1 );// Cursor selection bit in Display on cmd.
const uint8_t BLINK_ON_BIT   = ( 1 << 0 );// Blink selection bit on Display on cmd.

// Driver DDRAM addressing
const uint8_t dram_dispAddr [][3] =
{
   { 0x00, 0x00, 0x00 },  // One line display address
   { 0x00, 0x40, 0x00 },  // Two line display address
   { 0x00, 0x10, 0x20 }   // Three line display address
};
/*FUNCTION PROTOTYPE --- FUNCTION PROTOTYPE --- FUNCTION PROTOTYPE --- FUNCTION PROTOTYPE --- */
void LCD_ST7032_Init(ST7032_InitTypeDef *hlcd);
void LCD_command (uint8_t cmd);
void LCD_write_byte(uint8_t value);
void LCD_setCursor(uint8_t line_num, uint8_t x);
void LCD_custom(uint8_t custom_char[8],uint8_t custom_char_location);
void LCD_shift(uint8_t sc_rl_s,uint8_t shift_time);
void LCD_contrast(uint8_t contrast);
void LCD_backlight(uint8_t percentage);
void LCD_write(const char *buffer);
void LCD_clear(void);
void LCD_home(void);
void LCD_on(void);
void LCD_off(void);
void LCD_cursor_on(void);
void LCD_cursor_off(void);
void LCD_blink_on(void);
void LCD_blink_off(void);


// FUNCTIONS-----FUNCTIONS-----FUNCTIONS-----FUNCTIONS-----FUNCTIONS-----FUNCTIONS-----FUNCTIONS
/* Name: LCD_ST7032_Init
 * Function: Init LCD with ST7032 driver
 * @param: ST7032_InitTypeDef *hlcd: handle type def for ST7032 LCD
 *
 * @ref_url: http://www.newhavendisplay.com/app_notes/ST7032.pdf
 * @ref_url: http://www.farnell.com/datasheets/1811619.pdf?_ga=2.242926786.1981495964.1585344952-578440065.1585344952
 * */
void LCD_ST7032_Init(ST7032_InitTypeDef *hlcd)
{
	/*passing value to private variable*/
	_hlcd.LCD_hi2c = hlcd->LCD_hi2c;
	_hlcd.TIM_channel_backlight = hlcd->TIM_channel_backlight;
	_hlcd.LCD_htim_backlight = hlcd->LCD_htim_backlight;
	_hlcd.i2cAddr = (hlcd->i2cAddr << 1u);
	_hlcd.num_col = hlcd->num_col;
	_hlcd.num_lines = hlcd->num_lines;


	LCD_buff[0] = DISP_CMD;
	LCD_buff[1] = FUNC_SET_TBL0;
	HAL_I2C_Master_Transmit(_hlcd.LCD_hi2c,_hlcd.i2cAddr,LCD_buff,2,HAL_MAX_DELAY);
	HAL_Delay(CMD_DELAY);
	LCD_buff[0] = DISP_CMD;
	LCD_buff[1] = FUNC_SET_TBL1;//FUNC_SET_TBL1;
	LCD_buff[2] = 0x14;	//Internal OSC frequency
	LCD_buff[3] = 0x79;	//Contrast set
	LCD_buff[4] = 0x50;	//Power/ICON control/Contrast set
	LCD_buff[5] = 0x6C;	//Flower control
	LCD_buff[6] = DISP_ON_CMD;
	LCD_buff[7] = CLEAR_DISP_CMD;	//Clear Display
	HAL_I2C_Master_Transmit(_hlcd.LCD_hi2c,_hlcd.i2cAddr,LCD_buff,8,HAL_MAX_DELAY);
	_initialized = 1;
	HAL_Delay(CMD_DELAY);
}
/* Name: LCD_command
 * Function: Send command to LCD
 * @param: uint8_t cmd: defined CMD
 *
 * */
void LCD_command(uint8_t cmd)
{
	LCD_buff[0] = DISP_CMD;
	LCD_buff[1] = cmd;
	HAL_I2C_Master_Transmit(_hlcd.LCD_hi2c,_hlcd.i2cAddr,LCD_buff,2,HAL_MAX_DELAY);
	HAL_Delay(CMD_DELAY);
}
/* Name: LCD_setCursor
 * Function: set the Cursor position
 * @param: uint8_t line_num: line position
 * @param: uint8_t x: column position
 *
 * */
void LCD_setCursor(uint8_t line_num, uint8_t x)
{
   uint8_t base = 0x00;
   if ( _initialized )
   {
      // set the baseline address with respect to the number of lines of
      // the display
      base = dram_dispAddr[_hlcd.num_lines-1][line_num];
      base = SET_DDRAM_CMD + base + x;
      LCD_command( base );
   }
}
/* Name: LCD_write_byte
 * Function: write a byte to LCD
 * @param: uint8_t value: input 1 byte character
 *
 * */
void LCD_write_byte(uint8_t value)
{
   if ( _initialized )
   {
      if ( value == '\n' )
      {
         LCD_setCursor (1,0);
      }
      else
      {
        LCD_buff[0] = RAM_WRITE_CMD;
        LCD_buff[1] = value;
     	HAL_I2C_Master_Transmit(_hlcd.LCD_hi2c,_hlcd.i2cAddr,LCD_buff,2,HAL_MAX_DELAY);
     	HAL_Delay(CHAR_DELAY);
      }
   }
}

/* Name: LCD_write
 * Function: write a string to LCD
 * @param: const char *buffer: input string maximum 80 characters
 *
 * */
void LCD_write(const char *buffer)
{
	memset(LCD_buff,0,sizeof(LCD_buff));
	if ( _initialized )
	{
		sprintf((char *)LCD_buff,"%c%s",RAM_WRITE_CMD,buffer);
		HAL_I2C_Master_Transmit(_hlcd.LCD_hi2c,_hlcd.i2cAddr,LCD_buff,strlen((char *)LCD_buff),HAL_MAX_DELAY);
     	HAL_Delay(CHAR_DELAY);
	}
}

/* Name: LCD_custom
 * Function: CGRAM allows user to design and store up to 8 custom character
 * @param: cchar[8]: custom character designed by user and stored in an 8bit array
 * @param: cchar_location: location of custom character in CGRAM (0x00 -> 0x07)
 *
 * For writing custom character: call LCD_write_byte() with @param is the CGRAM character
 * location (0x00 -> 0x07)
 *
 * Ref link for learning: http://www.handsonembedded.com/lcd16x2-hd44780-tutorial-5/
 * */
void LCD_custom(uint8_t cchar[8],uint8_t cchar_location)
{
	if ((cchar_location >= 0) && (cchar_location < MAX_CCHAR))
	{
		uint8_t CGRAM_loc = cchar_location;
		CGRAM_loc *= 8;
		CGRAM_loc += 0x40; // 0x40 =  CGRAM base address
		if (_initialized)
		{
			LCD_command(FUNC_SET_TBL0);
			/*Set CGRAM in AC*/
			sprintf((char *)LCD_buff,"%c%c",DISP_CMD,CGRAM_loc);
			HAL_I2C_Master_Transmit(_hlcd.LCD_hi2c,_hlcd.i2cAddr,LCD_buff,2,HAL_MAX_DELAY);
			/*Write to CGRAM location just set*/
			LCD_write((char*)cchar);
			LCD_command(FUNC_SET_TBL1);
		}
	}
}
/* Name: LCD_shift
 * Function: Shif screen/cursor - right/left - with number of shift_time
 * @param: uint8_t sc_rl_s: screen/cursor sellect, defined in @ref screen_cursor_select
 * @param: uint8_t shift_time: number of shift time will be operated
 *
 * */
void LCD_shift(uint8_t sc_rl_s,uint8_t shift_time)
{
	LCD_command(FUNC_SET_TBL0); // set inst table 0
	for(int i = 0; i < shift_time; i++)
	{
		switch (sc_rl_s)
		{
		case SR:
			LCD_command(DISP_SHIFT_CMD | SR);
			break;
		case SL:
			LCD_command(DISP_SHIFT_CMD | SL);
			break;
		case CR:
			LCD_command(DISP_SHIFT_CMD | CR);
			break;
		case CL:
			LCD_command(DISP_SHIFT_CMD | CL);
			break;
		}
	}
	LCD_command(FUNC_SET_TBL1); // switch back inst table 1
}
/* Name: LCD_contrast
 * Function: Set contrast level for the LCD
 * @param: uint8_t contrast: contrast level of LCD (level 0 -> 15)
 *
 * */
void LCD_contrast(uint8_t contrast)
{
	if(_initialized && (contrast > 0) && (contrast < 16))
	{
		LCD_command(CONTRAST_CMD+contrast);
	}
}
/* Name: LCD_backlight
 * Function: Set backlight level for the LCD
 * @param: uint8_t percentage: backlight level 0->100
 * @param: TIM_OC_InitTypeDef *OC_init_param: Output capture init using for
 * 			PWM timer using for backlight
 * */
void LCD_backlight(uint8_t percentage)
{
	if(_initialized)
	{

		if((percentage >= 0) && (percentage <=100))
		{
			uint16_t CCR_value = (percentage * _hlcd.LCD_htim_backlight->Init.Period) / 100;
			TIM_OC_InitTypeDef TIMPWM_param;
			TIMPWM_param.OCMode = TIM_OCMODE_PWM1;
			TIMPWM_param.Pulse = CCR_value+1;
			TIMPWM_param.OCFastMode = TIM_OCFAST_DISABLE;
			TIMPWM_param.OCPolarity = TIM_OCPOLARITY_HIGH;
			if (HAL_TIM_PWM_ConfigChannel(_hlcd.LCD_htim_backlight,&TIMPWM_param,_hlcd.TIM_channel_backlight) != HAL_OK)
			{
				Error_Handler();
			}
		}

		HAL_TIM_PWM_Start(_hlcd.LCD_htim_backlight,_hlcd.TIM_channel_backlight);
	}
}
/*LCD AND CURSOR CONTROL ---  LCD AND CURSOR CONTROL ---  LCD AND CURSOR CONTROL ---  */
void LCD_clear(void)
{
   LCD_command (CLEAR_DISP_CMD);
}
void LCD_home(void)
{
	LCD_command ( HOME_CMD );
}
void LCD_on(void)
{
	LCD_command ( DISP_ON_CMD );
}
void LCD_off(void)
{
	LCD_command ( DISP_OFF_CMD );
}
void LCD_cursor_on(void)
{
	LCD_command ( DISP_ON_CMD | CURSOR_ON_BIT );
}
void LCD_cursor_off(void)
{
	LCD_command ( DISP_ON_CMD & ~(CURSOR_ON_BIT) );
}
void LCD_blink_on(void)
{
	LCD_command ( DISP_ON_CMD | BLINK_ON_BIT );
}
void LCD_blink_off(void)
{
	LCD_command ( DISP_ON_CMD & ~(BLINK_ON_BIT) );
}








