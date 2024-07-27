/*
 * my_pll.h
 *
 *  Created on: Jul 24, 2024
 *      Author: sinha
 */

#ifndef INC_MY_PLL_H_
#define INC_MY_PLL_H_


#define PLL_M       8ul
#define PLL_N       180ul
#define PLL_P       0ul
#define PLL_Q       2ul

#define HCLK_FREQ       180000000uL
#define APB1_FREQ       (HCLK_FREQ/4)
#define APB2_FREQ       (HCLK_FREQ/2)

void clockSpeed_PLL();


#endif /* INC_MY_PLL_H_ */
