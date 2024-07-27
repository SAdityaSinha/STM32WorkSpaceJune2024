/*
 * TIM2.c
 *
 *  Created on: Jul 24, 2024
 *      Author: sinha
 */
#include"TIM2.h"

void set_TIM2()
{
	RCC->APB1ENR |= (1<<0);
	//setting up for TIM2
	TIM2->PSC = 16000-1;		//to get 16MHz
	TIM2->ARR = 1000-1;			//

	TIM2->CNT = 0;

	TIM2->CR1 |= (1<<0);
	TIM2->CCER |= (1<<0);
	TIM2->CCMR1 |= (1<<4);
	TIM2->CCMR1 |= (6<<4);			//IDK why this and the upper line
}


void set_LD5_AF()
{
	RCC->AHB1ENR |= (1<<0);	//enabling the pin for the GPIOA

	GPIOA->MODER |= (1<<11);	//==(2<<10);
	GPIOA->OSPEEDR |= (1<<10);

	GPIOA->AFR[0] |= (1<<20);
	GPIOA->AFR[0] &= ~(7<<21);

	//setting up complete now toggle LD5 pin
	//to get the blinking light
}

void set_PA0_AF()
{
	RCC->AHB1ENR |= (1<<0);	//enabling the pin for the GPIOA

	GPIOA->MODER |= (1<<1);	//==(2<<0);
	GPIOA->OSPEEDR |= (1<<0);

	GPIOA->AFR[0] |= (1<<0);
	//to get the blinking light
}

void TIM2_DutyCycle(uint32_t DutyCycle)
{
	TIM2->CCR1=(DutyCycle*TIM2->ARR)/100;
}



