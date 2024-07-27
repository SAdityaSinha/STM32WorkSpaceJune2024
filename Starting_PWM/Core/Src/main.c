/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include<stdint.h>
#include "main.h"
#include "TIM2.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

///////////////////////////////////////////
//////////////////////////////////////////

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int main()
{
	set_TIM2();
	set_PA0_AF();


	uint32_t val;
	while(1)
	{
		for(val = 0; val<255;val++)
		{
			TIM2_DutyCycle(val*10);
			for(int i=0;i<1000;i++);
		}
		for(val =255;val>10;val--)
		{
			TIM2_DutyCycle(val*10);
			for(int i=0;i<1000;i++);
		}
	}
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
