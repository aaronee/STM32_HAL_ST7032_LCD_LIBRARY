/*
 * main.h
 *
 *  Created on: Mar. 13, 2020
 *      Author: khoahuynh
 */

#ifndef INC_MAIN_H_
#define INC_MAIN_H_

#include "stm32f103xb.h"
#include "stm32f1xx_hal.h"

void SYSCLK_Init(void);
void GPIO_Init(void);
void Error_Handler(void);
void TIM_Init(void);
void I2C_Init(void);

extern TIM_HandleTypeDef htim2;
extern I2C_HandleTypeDef hi2c1;


#endif /* INC_MAIN_H_ */
