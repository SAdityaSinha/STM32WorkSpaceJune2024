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
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

//working with ADC

//#include"my_ADC.h"
//#include"my_pll.h"
////#include"my_sysTick.h"
//#include"my_Serial.h"

/* USER CODE END Includes */


/* USER CODE BEGIN Includes */

//#if !defined(__SOFT_FP__) && defined(__ARM_FP)
//  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
//#endif

#include <stdint.h>

#include<stdio.h>

#include "my_pll.h"
#include "my_Serial.h"
#include "my_ADC.h"





int main(){

    clockSpeed_PLL();

    tx_init();
    adc_init();
    adc_int_init();

    adc_start_conversion();

    while(1){

    };
}

int __io_putchar(int ch){
    tx_send(ch);
    for(uint32_t i=0;i<500000;i++);
    return ch;
}


/* USER CODE END Includes */


