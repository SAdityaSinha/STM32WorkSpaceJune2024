/*
 * my_sysTick.h
 *
 *  Created on: Jul 24, 2024
 *      Author: sinha
 */

#ifndef INC_MY_SYSTICK_H_
#define INC_MY_SYSTICK_H_

void SysTick_Init();
void SysTick_Handler();
void delay_ms(uint32_t ms);
uint32_t getMillis();

#endif /* INC_MY_SYSTICK_H_ */
