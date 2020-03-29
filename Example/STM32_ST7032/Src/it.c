/*
 * it.c
 *
 *  Created on: Mar. 13, 2020
 *      Author: khoahuynh
 */
#include "main.h"
#include "it.h"
//#include "DMX_data_stream.h"

//uint16_t cnt = 0;

void SysTick_Handler(void)
{
	HAL_SYSTICK_IRQHandler();
	HAL_IncTick();
}
