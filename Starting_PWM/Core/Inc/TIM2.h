/*
 * TIM2.h
 *
 *  Created on: Jul 24, 2024
 *      Author: sinha
 */
#include<stdint.h>
#include"main.h"
#ifndef INC_TIM2_H_
#define INC_TIM2_H_

/////////////////////////////////
void set_TIM2();
void set_LD5();
void set_PA0_AF();
void TIM2_DutyCycle(uint32_t DutyCycle);
////////////////////////////////

#endif /* INC_TIM2_H_ */

/*
 *
 *
#include <stdint.h>
#include<stm32f4xx.h>
void PA5_PWM_Config();
void TIM2_PWM_Config();
void TIM2_PA5_DutyCycle(uint32_t);
void delay();
int main(void)
{
    PA5_PWM_Config();
    TIM2_PWM_Config();
    unsigned DC=0;
    while(1)
    {
    	for(DC=0;DC<10;DC++)
    	{
    		TIM2_PA5_DutyCycle(DC*10);
    		delay(100000);
    	}
    	for(DC=10;DC>0;DC--)
    	    	{
    	    		TIM2_PA5_DutyCycle(DC*10);
    	    		delay(200000);
    	    	}

    }

}
void PA5_PWM_Config()
{
	RCC->AHB1ENR|=(1<<0);
	GPIOA->MODER &=~(1<<10);
	GPIOA->MODER |=(1<<11);
	GPIOA->AFR[0] |=(1<<20);
	GPIOA->AFR[0] &=~(7<<21);
}
void TIM2_PWM_Config()
{
	RCC ->APB1ENR |=(1<<0);
	TIM2->PSC=0;
	TIM2->CNT=0;
	TIM2->CR1 |=(1<<0);
	TIM2->CCER |=(1<<0);
	TIM2->CCMR1 |=(1<<4);
	TIM2->CCMR1 |=(6<<4);
	TIM2->ARR=16000000/1000;
}
void TIM2_PA5_DutyCycle(uint32_t DutyCycle)
{
	TIM2->CCR1=(DutyCycle*TIM2->ARR)/100;
}
void delay(uint32_t us)
{
	uint32_t i=0;
	for(i=0;i<us;i++);
}
 *
 *
 */
