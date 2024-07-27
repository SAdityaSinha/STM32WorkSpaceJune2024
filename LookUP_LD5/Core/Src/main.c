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


/* USER CODE END Includes */

/* USER CODE BEGIN PFP */



/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



#include <stdint.h>
#include "stm32f446xx.h"

// Function prototypes
void clockSpeed_PLL(void);
void adc_init(void);
void adc_start_conversion(void);
uint32_t adc_read(void);
void dac_init(void);
void dac_set_value(uint32_t value);

// Lookup table for DAC values
#define LOOKUP_TABLE_SIZE 16
uint32_t lookup_table[LOOKUP_TABLE_SIZE] = {
    0,    // 0V
    256,  // 0.8V
    512,  // 1.6V
    768,  // 2.4V
    1024, // 3.2V
    1280, // 4.0V
    1536, // 4.8V
    1792, // 5.6V
    2048, // 6.4V
    2304, // 7.2V
    2560, // 8.0V
    2816, // 8.8V
    3072, // 9.6V
    3328, // 10.4V
    3584, // 11.2V
    4095  // 12.0V
};

int main(void) {
    clockSpeed_PLL(); // Set clock speed (assuming this function sets the clock speed)

    adc_init(); // Initialize ADC
    dac_init(); // Initialize DAC

    while (1) {
        // Start ADC conversion
        adc_start_conversion();

        // Read ADC value
        uint32_t adc_value = adc_read();

        // Map ADC value to DAC value using the lookup table
        // Assuming adc_value is in the range of 0 to 4095 (12-bit ADC)
        uint32_t index = (adc_value * LOOKUP_TABLE_SIZE) / 4096; // Calculate index
        if (index >= LOOKUP_TABLE_SIZE) index = LOOKUP_TABLE_SIZE - 1; // Prevent overflow

        // Set DAC output based on the lookup table value
        dac_set_value(lookup_table[index]);

        for (volatile uint32_t i = 0; i < 500000; i++); // Delay
    }

    return 0;
}

// Clock speed setting function (to be implemented as per your requirements)
void clockSpeed_PLL(void) {
    // Implementation to set the clock speed
}

// ADC initialization function
void adc_init(void) {
    // Enable ADC1 clock
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    // Configure ADC (Assuming single conversion mode, continuous mode, etc.)
    ADC1->CR1 = 0; // Set to default
    ADC1->CR2 = ADC_CR2_ADON; // Enable ADC

    // Configure channel (Assuming channel 0 for this example)
    ADC1->SQR3 = 0; // Channel 0
}

// Start ADC conversion
void adc_start_conversion(void) {
    ADC1->CR2 |= ADC_CR2_SWSTART; // Start conversion
}

// Read ADC value
uint32_t adc_read(void) {
    while (!(ADC1->SR & ADC_SR_EOC)); // Wait for conversion complete
    return ADC1->DR; // Read data
}

// DAC initialization function
void dac_init(void) {
    // Enable GPIOA clock for DAC
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Set PA4 to analog mode
    GPIOA->MODER &= ~(3<<8); // Clear bits 8-9
    GPIOA->MODER |= (3<<8);  // Set PA4 to analog mode

    // Enable DAC clock
    RCC->APB1ENR |= (1 << 29);

    // Enable DAC channel 1
    DAC->CR |= DAC_CR_EN1;
    DAC->CR |= DAC_CR_BOFF1; // Enable output buffer
}

// Set DAC output value
void dac_set_value(uint32_t value) {
    DAC->DHR12R1 = value; // Set the output to DAC
    DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1; // Trigger the DAC
}

// Placeholder for UART transmission function
void tx_send(int ch) {
    // Implementation of UART transmission
}

// Override the default putchar function
int __io_putchar(int ch) {
    tx_send(ch);
    for (uint32_t i = 0; i < 500000; i++);
    return ch;
}




/*
#include<stdio.h>
#include<stddef.h>
#include<stdint.h>
#include "stm32f446xx.h"

volatile uint8_t brightness = 0; // Initial brightness (0-100)

void Timer2_init();
void Enable_GPIOA_LED();
void GPIOA_LED_SetBrightness(uint8_t brightness);

int main() {
    // Enable GPIOA and GPIOC clocks
    RCC->AHB1ENR |= (1 << 0) | (1 << 2);
    // Enable SYSCFG clock
    RCC->APB2ENR |= (1 << 14);

    // Configure PA5 as alternate function for TIM2
    GPIOA->MODER &= ~(3 << 10);
    GPIOA->MODER |= (2 << 10);
    GPIOA->AFR[0] |= (1 << 20); // AF1 for TIM2

    // Configure PC13 as input (button)
    GPIOC->MODER &= ~(3 << 26);

    __disable_irq();

    // Configure external interrupt for PC13
    SYSCFG->EXTICR[3] |= (2 << 4);
    EXTI->IMR |= (1 << 13);
    EXTI->FTSR |= (1 << 13);

    NVIC_EnableIRQ(EXTI15_10_IRQn);

    __enable_irq();

    Timer2_init();
    Enable_GPIOA_LED();

    while(1) {
        // Main loop can be empty as the work is done in the interrupt
    }
}

void EXTI15_10_IRQHandler(void) {
    if (EXTI->PR & (1 << 13)) {
        EXTI->PR |= (1 << 13); // Clear the interrupt pending bit
        brightness = (brightness + 10) % 110; // Increase brightness by 10%, wrap around to 0 after 100%
        GPIOA_LED_SetBrightness(brightness);
    }
}

void Timer2_init() {
    RCC->APB1ENR |= (1 << 0); // Enable TIM2 clock
    TIM2->PSC = 16000 - 1;    // Set prescaler to 16000 (1ms period)
    TIM2->ARR = 100 - 1;      // Set auto-reload value for 100 steps (1% resolution)
    TIM2->CCR1 = 0;           // Initialize the duty cycle to 0%
    TIM2->CCMR1 |= (6 << 4);  // Configure TIM2 in PWM mode 1
    TIM2->CCER |= (1 << 0);   // Enable capture/compare for channel 1
    TIM2->CR1 |= (1 << 0);    // Enable TIM2
}

void Enable_GPIOA_LED() {
    // GPIOA already enabled and PA5 configured in main()
}

void GPIOA_LED_SetBrightness(uint8_t brightness) {
    TIM2->CCR1 = brightness; // Set the duty cycle (0-100)
}

/*

/* USER CODE END 0 */

