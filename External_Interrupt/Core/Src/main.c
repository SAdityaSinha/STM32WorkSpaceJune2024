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

/* USER CODE BEGIN Includes */

// writing the steps to follow
/*
 *  1. configure the clocks
 *  2.setting up the interrupt
 *  	1. syscfg4 --> C13th pin
 *  	2. exti->IMR -->
 *  	3. ->firsr
 *  	4. NVIC call ext15_10 IRQ
 *
 *
 *
 */

#include"main.h"

int rate = 100;

void set_GPIO_A_C()
{
  GPIOA->MODER |= (1<<10);
//  GPIOA->OTYPER &= ~(1<<5);
  GPIOA->OSPEEDR |= (1<<10);
  //GPIOA->PUPDR &= ~(3<<10);

  //GPIOC->MODER &= ~(3<<26);
  //GPIOC->OTYPER &= ~(1<<13);
  //GPIOC->OSPEEDR |= (3<<26);
}


void blink()
{
	GPIOA->ODR ^= (1<<5);
	for(int i=0;i<5000*rate;i++);
}


void EXTI15_10_IRQHandler()
{
	EXTI->PR |= (1<<13); // for reseting
	rate = 10;
	blink();
}



int main()
{
	RCC->AHB1ENR |= (1<<0)	| (1<<2);	//enabling for GPIOA and C
	RCC->APB2ENR |= (1<<14);

	set_GPIO_A_C();


	__disable_irq();		//disabling the IRQ -- so that we do not accept any interrupt at the time of setting up things

	SYSCFG->EXTICR[3] |= (2<<4);	//setting up the EXTI13 pin
	EXTI->IMR |= (1<<13);
	EXTI->FTSR |= (1<<13);

	NVIC_EnableIRQ(40);

	__enable_irq();

	while(1)
	{
		blink();
	}


}






/* USER CODE END Includes */
