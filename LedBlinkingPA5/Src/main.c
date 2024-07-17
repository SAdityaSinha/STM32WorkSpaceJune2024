/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
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

#define OriginalCodeStyle
// #undef OriginalCodeStyle

 #define UseLibraryCode
 #undef UseLibraryCod 


#ifdef OriginalCodeStyle  

	#include <stdint.h>
	#include <stdio.h>
	#include <stddef.h>
	#include<stdbool.h>

	#include"blinkLED.h"
	#include"RCC_GPIO.h" 		//a better pre-written file exist that has everything "core_cm.h"
	// adding the github link :

	#if !defined(__SOFT_FP__) && defined(__ARM_FP)
	#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
	#endif

	void blinkLedXtime(int times)
	{
		for(int i=0;i<=times;i++)
		{
			GPIOA->ODR |= (1<<5);
			normalDelay(50);
			GPIOA->ODR &=~(1<<5);
			normalDelay(25);
		}
	}


	void blinkLedNormaly(int delayAmount)
	{
		GPIOA->ODR |= (1<<5);
		normalDelay(delayAmount);
		GPIOA->ODR &=~(1<<5);
		normalDelay(delayAmount);
	}


	int main(void)
	{
	//	Blink LED in different speed one after another
		/*
		* STEPs to program
		* Enable clk RCC_AHB1 on port A
		* Configure Port A5 (PA5) as output mode as GPIOx_MODDER
		*
		*/

		*RCC|=(1<<0); //this is to enable the GPIOA

		GPIOA->MODER |= (1<<10);					//PA5 mode OUTPUT (01)
		GPIOA->OTYPER &=~(1<<5);					//
		GPIOA->OSPEEDR |=~(1<<10);

		GPIOA->PUPDR &=~(3<<10);


		*RCC|=(1<<2); //enabling the clock at GPIOC
//		setting GPIOC for accepting PC13
		bool isInputPortSet = false;
		GPIOC->MODER &= ~(3<<13);
		GPIOC->OTYPER &= ~(1<<13);
		GPIOC->OSPEEDR &= ~(3<<13);
		isInputPortSet = true;

		printf("Hello World!!!\n");
		bool buttonStatus;


		////////////////////////
		// for creating the pass code to unlock(blink);
		short int onTime =0;
		int inputDetected;
		//setting the pass code
		// 0(short press)	:	1(long press)
		int a[4] = {0,1,1,0};
		// 4 bool for managing seriality of code
		bool passVerifier[4] = {false,false,false,false}; 	
		bool isVerified = false;

		GPIOA->ODR &=~(1<<5); //force setting it to off
//		GPIOA->ODR |= (1<<5);
//		normalDelay(100);
		/* Loop forever */
		for(;;)
		{

//			GPIOA->ODR |= (1<<5);


			if(isVerified)
			{
				printf("Veriffied\n");
				blinkLedNormaly(10);
			}else
			{

				buttonStatus = GPIOC->IDR & (1<<13);
	//			printf("%d \n",GPIOC->IDR);
				if(!isButton2Pressed(isInputPortSet,buttonStatus))
				{
					onTime +=1;
//					printf(" ON : %d \n",onTime);		//making on<=3 && on>0 as short press 0
												//and on>3 as long press 1

	//				printf("Main - true\n");
	//				blinkLedNormaly(11);
				}else
				{
//					printf("Released Button\n");
					if(onTime>0 && onTime<=30000)
					{
						inputDetected = 0;
						blinkLedXtime(1);
					}else if (onTime>30000)
					{
						inputDetected =1;
						blinkLedXtime(5);
					}

//					GPIOA->ODR &=~(1<<5); //force off
					isVerified = updateOnButtonRelease(a,passVerifier,inputDetected);
					onTime = 0;


	//				blinkLedNormaly(5);
	//				printf("Main - false\n");
				}
			}
		}

	}
#endif
