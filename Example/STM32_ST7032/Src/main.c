/*
 *	@File: main.c
 *	@This file is free to be used, modified. This header must be remained. Thank you.
 *
 *	@Introduction: This file is the example code for the library STM32_ST7032
 *				> Implement using Blue Pill stm32f103c8t6 and LCD MIDAS MCCOG21605B6W-BNMLWI
 *				> Implement TIM2 channel 2 for PWM signal to control backlight
 *				> Implement I2C1 to communicate with LCD
 *				> SCL - B9 ; SDA - B8 ; backlight PWM - A1
 *	@Bugs/requests: please contact via email, thank you.
 *
 *  @Created on: Mar. 27, 2020
 *  @Author: AARONEE - khoahuynh
 * 	@Email: khoahuynh.ld@gmail.com
 * 	@Github: https://github.com/khoahuynhld
 */
#include "main.h"
#include <stdio.h>
#include <string.h>
#include "STM32_ST7032.h"

TIM_HandleTypeDef htim2 = {0};
I2C_HandleTypeDef hi2c1 = {0};
char mesg[80] = "hello";
/* create bell shape character to (5pixel x 8pixel)
 * 0x04: x-x-x-0-0-1-0-0
 * 0x0E: x-x-x-0-1-1-1-0
 * 0x0E: x-x-x-0-1-1-1-0
 * 0x0E: x-x-x-0-1-1-1-0
 * 0x0E: x-x-x-0-1-1-1-0
 * 0x0F: x-x-x-1-1-1-1-1
 * 0x04: x-x-x-0-0-1-0-0
 * 0x00: x-x-x-0-0-0-0-0
 * */
uint8_t bell[8] = {0x04,0x0E,0x0E,0x0E,0x0E,0x1F,0x04,0x00};

int main(void)
{
	/* Sof Initialize code */
	HAL_Init();
	GPIO_Init();
	SYSCLK_Init();
	TIM_Init();
	I2C_Init();
	HAL_Delay(10);
	/*End of Initialize code*/

	/*Define ST7032_InitTypeDef*/
	ST7032_InitTypeDef MIDAS = {0};
	MIDAS.LCD_hi2c = &hi2c1;
	MIDAS.LCD_htim_backlight = &htim2;
	MIDAS.TIM_channel_backlight = TIM_CHANNEL_2;
	MIDAS.i2cAddr = 0x3E;
	MIDAS.num_col = 16;
	MIDAS.num_lines = 2;
	/*End of Define ST7032_InitTypeDef*/

	LCD_ST7032_Init(&MIDAS);	// Init LCD
	LCD_backlight(75);			// set backlight as 75%
	LCD_clear();				// clear LCD
	LCD_custom(bell,0);			// load "bell" character to first slot (8 in total)
	LCD_home(); 				// set cursor and shift screen to home
	LCD_write(mesg);			// right "mesg" to screen
	LCD_cursor_on();			// set cursor on
	LCD_shift(CR,2);			// shift cursor by 2 slot
	LCD_write_byte(0x00);		// write "bell" character to screen; "0x00" is the first custom character
	LCD_contrast(15);			// set contrast to level 15 - MAXIMUM (15 level available)

	while(1);

	return 0;
}
/*SYSTEM INIT			SYSTEM INIT			SYSTEM INIT			SYSTEM INIT			SYSTEM INIT*/

/* Name: Error_Handler
 * Function: while loop to trap processor when error occur
 * @param: void
 *
 * */
void Error_Handler(void)
{
	while(1);
}
/* Name: SYSCLK_Init
 * Function: Init SYSCLK HCLK ABP-CLK
 * @param: void
 *
 * */
void SYSCLK_Init(void)
{
	RCC_OscInitTypeDef OSCinit_param = {0};
	OSCinit_param.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	OSCinit_param.HSEState = RCC_HSE_ON;
	OSCinit_param.PLL.PLLState = RCC_PLL_ON;
	OSCinit_param.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	OSCinit_param.PLL.PLLMUL = RCC_PLL_MUL6; // HSE x6 = 48MHz
	/*SYSCLK = 8MHz HSE PD0/PD1*/
	if (HAL_RCC_OscConfig(&OSCinit_param) != HAL_OK)
	{
		Error_Handler();
	}
	RCC_ClkInitTypeDef CLKinit_param = {0};
	CLKinit_param.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
								RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	CLKinit_param.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; // 48M
	CLKinit_param.AHBCLKDivider = RCC_SYSCLK_DIV1;	// 48M
	CLKinit_param.APB1CLKDivider = RCC_HCLK_DIV8;	// 48M/8 = 6M
	CLKinit_param.APB2CLKDivider = RCC_HCLK_DIV8;	//
	if( HAL_RCC_ClockConfig(&CLKinit_param,FLASH_LATENCY_1) != HAL_OK)
	{
		Error_Handler();
	}
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	__HAL_RCC_HSI_DISABLE(); // Disable HSI

}
/* Name: GPIO_Init
 * Function: Init GPIO
 * @param: void
 *
 * */
void GPIO_Init(void)
{
	/* Set up port D , pin PD0 as OSC in, PD1 as OSC out*/
	__HAL_RCC_GPIOD_CLK_ENABLE();
}
/* Name: TIM_Init
 * Function: Init Timmer - This timer is used to control LCD backlight
 * @param: void
 *
 * */
void TIM_Init(void)
{
	/*TIM2---TIM2---TIM2---TIM2---TIM2---TIM2---TIM2---TIM2---TIM2---TIM2*/
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 49;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 1999;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

	if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
	TIM_OC_InitTypeDef TIM2PWM_param;
	TIM2PWM_param.OCMode = TIM_OCMODE_PWM1;
	TIM2PWM_param.Pulse = 500;
	TIM2PWM_param.OCFastMode = TIM_OCFAST_DISABLE;
	TIM2PWM_param.OCPolarity = TIM_OCPOLARITY_HIGH;
	if (HAL_TIM_PWM_ConfigChannel(&htim2,&TIM2PWM_param,TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
}
/* Name: I2C_Init
 * Function: Init I2C - This I2C is used to comminicate with LCD
 * @param: void
 *
 * */
void I2C_Init (void)
{
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 200000; // 200Khz
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0x01;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT; // 7bit address

	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		Error_Handler();
	}

}
