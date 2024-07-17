/*
 * RCC_GPIO.h
 *
 *  Created on: Jul 15, 2024
 *      Author: sinha
 */

#ifndef INC_RCC_GPIO_H_
#define INC_RCC_GPIO_H_



#include<stdint.h>

#define __IO volatile

#define RCC_BASE		(0x40023800)			//Base address for RCC peripheral on AHB! BUS
#define RCC_OFFSET		(RCC_BASE + 0x30)					//Offset for RCC_AHB1ENC
#define RCC		((__IO uint32_t*)RCC_OFFSET)

typedef struct{
	__IO uint32_t MODER;
	__IO uint32_t OTYPER;
	__IO uint32_t OSPEEDR;
	__IO uint32_t PUPDR;
	__IO uint32_t IDR;
	__IO uint32_t ODR;
	__IO uint32_t BSRR;
	__IO uint32_t LCKR;
	__IO uint32_t AFR[2];

}GPIO_TypeDef;

//defining for GPIOA
#define GPIOA_BASE 					(0x40020000)
#define GPIOA  						((GPIO_TypeDef *)GPIOA_BASE)

//defining for GPIOC  defining for C now using it to get PCA13
#define GPIOC_BASE                  (0x40020800)
#define GPIOC                       ((GPIO_TypeDef *)GPIOC_BASE)


#define ENABLE_LED2 (GPIOA->ODR |= (1<<5))
#define DISABLE_LED2 (GPIOA->ODR &= ~(1<<5))

// #define USER_BUTTON ()


#endif /* INC_RCC_GPIO_H_ */
