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

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
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

/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 */

#include "stm32f446xx.h"
#define MAX_PASSWORD_LENGTH 5

void UART2_Init(void);
void UART_SendString(char *str);
void delay(uint32_t delay);
void UART_GetString(char *str, uint8_t max_length);
int Str_Comp(const char *OG, const char *USR);

int main(void)
{
    char OG_pass[MAX_PASSWORD_LENGTH + 1]; // +1 for null terminator
    strcpy(OG_pass, "pass");

    char USR_pass[MAX_PASSWORD_LENGTH + 1];

    // Initialize UART2
    UART2_Init();

    UART_SendString("Enter Your Password: ");
    UART_GetString(USR_pass, MAX_PASSWORD_LENGTH);

    if (Str_Comp(OG_pass, USR_pass)) {
        UART_SendString("\nPassword correct\n");
    } else {
        UART_SendString("\nPassword incorrect\n");
    }

    while (1) {
        for (int i = 0; i < 0xffff; i++);
    }
}

int Str_Comp(const char *OG, const char *USR)
{
    for (int i = 0; i < MAX_PASSWORD_LENGTH; i++) {
        if (OG[i] != USR[i]) {
            return 0; // Mismatch
        }
    }
    return 1; // Match
}

void UART_GetString(char *str, uint8_t max_length)
{
    uint8_t i = 0;
    while (i < max_length) {
        while (!(USART2->SR & USART_SR_RXNE)); // Wait for data
        char c = USART2->DR;
        if (c == '\r' || c == '\n') {
            break;
        }
        *str++ = c;
        i++;
    }
    *str = '\0'; // Null terminate the string
}


void UART2_Init(void)
{
    // 1. Enable the UART CLOCK and GPIO CLOCK
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;  // Enable USART2 clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;   // Enable GPIOA clock

    // 2. Configure the UART PINs for Alternate Functions
    GPIOA->MODER &= ~((3 << 4) | (3 << 6));  // Clear PA2 and PA3
    GPIOA->MODER |= (2 << 4) | (2 << 6);     // Set PA2 and PA3 to Alternate Function
    GPIOA->AFR[0] |= (7 << 8) | (7 << 12);   // Set AFRL for PA2 and PA3 to AF7 (USART2)

    // 3. Enable the USART by writing the UE bit in USART_CR1 register to 1.
    USART2->CR1 |= USART_CR1_UE;

    // 4. Program the M bit in USART_CR1 to define the word length.
    USART2->CR1 &= ~USART_CR1_M;  // 8 data bits

    // 5. Select the desired baud rate using the USART_BRR register.
    USART2->BRR = 0x8B;  // Assuming 16 MHz PCLK1, 115200 baud rate

    // 6. Enable the Transmitter/Receiver by Setting the TE and RE bits in USART_CR1 Register
    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE;
}

void UART_SendString(char *str)
{
    while (*str)
    {
        // Wait until TXE (Transmit data register empty) flag is set
        while (!(USART2->SR & USART_SR_TXE));

        // Send the character
        USART2->DR = (*str & 0xFF);

        // Move to the next character
        str++;
    }
}

/* USER CODE END PTD */