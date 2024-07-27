#include "main.h"
#include <stdbool.h>

//#define MASTER_BOARD
 #define SLAVE_BOARD

volatile uint32_t isVerified = 0;

void setUP_SPI1_Master();
void setUP_SPI1_Slave();

void button_PB13();
void Slave_LD5();

int main()
{
#ifdef SLAVE_BOARD

    setUP_SPI1_Slave();
    Slave_LD5();

    while (1)
    {
        while (!(SPI1->SR & (1U << 0))); // Wait until RXNE is set
        isVerified = SPI1->DR; // Read data
        if (isVerified == 1)
        {
            GPIOA->ODR ^= (1U << 5); // Toggle PA5
        }
    }

#endif

#ifdef MASTER_BOARD
    setUP_SPI1_Master();
    button_PB13();

    while (1)
    {
        if (!(GPIOC->IDR & (1U << 13)))
        {
            isVerified = 1;
            while (!(SPI1->SR & (1U << 1))); // Wait until TXE is set
              // Send data
        }
    }

#endif

}

void setUP_SPI1_Master()
{
    RCC->APB2ENR |= (1U << 12);
    RCC->AHB1ENR |= (1U << 0) | (1U << 1);

    // SPI SCK, MISO, MOSI pin configuration (PA5, PA6, PA7)
    GPIOA->MODER |= (2U <<10) | (2U << 12) | (2U << 14); // AF
    GPIOA->AFR[0] |= (5U << 20) | (5U << 24) | (5U << 28); // AF5 for SPI1

    SPI1->CR1 = 0; // Clear CR1 register
    SPI1->CR1 |= (1U << 2) | (3U << 3) | (1U << 9) | (1U << 8); // Master mode, Baud rate, SSI, SSM
    SPI1->CR1 |= (1U << 6);
}

void setUP_SPI1_Slave()
{
    RCC->APB2ENR |= (1<<12); // Enable SPI1 clock

    RCC->AHB1ENR |= (1<<0);
    // SPI SCK, MISO, MOSI pin configuration (PA5, PA6, PA7)
    GPIOA->MODER |= (2<<10) | (2<<12) | (2<<14); // AF mode
    GPIOA->AFR[0] |= (5<<20) | (5<<24) | (5<<14); // AF5 for SPI1

    SPI1->CR1 = 0; // Clear CR1 register
    SPI1->CR1 &= ~(1<<2); // Slave mode
    SPI1->CR1 |= (1<<9) | (1<<8); // SSI, SSM
    SPI1->CR1 |= (1<<6); // Enable SPI
}


void button_PB13()
{
    RCC->AHB1ENR |= (1<<2);
    GPIOC->MODER &= ~(3<<26);
    GPIOC->PUPDR |= (2<<26);
}

void Slave_LD5()
{
    RCC->AHB1ENR |= (1<<0);
    GPIOA->MODER |= (1<<10);
    GPIOA->OTYPER &= ~(1<<5);
    GPIOA->OSPEEDR |= (3<<10);
    GPIOA->PUPDR &= ~(3<<10);
}
