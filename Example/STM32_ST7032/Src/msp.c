/*
 * msp.c
 *
 *  Created on: Mar. 13, 2020
 *      Author: khoahuynh
 */
#include "main.h"

void HAL_MspInit(void)
{
	// HERE WE DO LOW LEVEL PROCESSOR SPECIFIC INIT - chap5vid3
	//1. Set up the priority grouping of the ARM cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4); // set interrupt priority grouping - chap5vid4
	//2. Enable the required system exceptions of the ARM cortex mx processor
	SCB->SHCSR |= 0x07 << 16; // Enable usagefault-memoryfault-busfault system exceptions- chap5vid5
	//3. Set up the priority if the system exceptions
	HAL_NVIC_SetPriority(MemoryManagement_IRQn,0,0);// - chap5vid5
	HAL_NVIC_SetPriority(BusFault_IRQn,0,0);// - chap5vid5
	HAL_NVIC_SetPriority(UsageFault_IRQn,0,0);// - chap5vid5

	__HAL_RCC_AFIO_CLK_ENABLE(); // ENABLE AFIO to mapping pins alternate function
}

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
	if (hi2c->Instance == hi2c1.Instance)
	{
		// Enable clk for I2C and GPIOB
		__HAL_RCC_I2C1_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		// Config IO for I2C1
		GPIO_InitTypeDef I2C1IO_param;
		I2C1IO_param.Mode = GPIO_MODE_AF_PP;
		I2C1IO_param.Pin = GPIO_PIN_8 | GPIO_PIN_9;
		I2C1IO_param.Pull = GPIO_NOPULL;
		I2C1IO_param.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOB,&I2C1IO_param);

		__HAL_AFIO_REMAP_I2C1_ENABLE();
		// Enable Interrupt in NVIC
		HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
		HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
		HAL_NVIC_SetPriority(I2C1_EV_IRQn,15,0);
		HAL_NVIC_SetPriority(I2C1_ER_IRQn,15,0);
	}
}
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == htim2.Instance)
	{
		//	Enable clk for TIM2 and GPIOB
		__HAL_RCC_TIM2_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();

		// Config IO for TIM2 PWM output
		GPIO_InitTypeDef TIM2PWMIO_param;
		TIM2PWMIO_param.Mode = GPIO_MODE_AF_PP;
		TIM2PWMIO_param.Pin = GPIO_PIN_1;
		TIM2PWMIO_param.Pull = GPIO_PULLUP;
		TIM2PWMIO_param.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOA,&TIM2PWMIO_param);
	}
}
