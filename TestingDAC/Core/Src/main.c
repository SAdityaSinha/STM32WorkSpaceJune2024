#include <stdint.h>
//#include "stm32f446xx.h"
#include"main.h"

#if !defined(_SOFT_FP) && defined(_ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

/*
 * dac.c
 *
 * author: Salahuddin
 * description:
 *   uses DAC channel 1 connected to PA4 to generate
 *   a ramp waveform
 *   DAC is setup to use software trigger
 *   as the source, and it needs to be triggered
 *   manually
 *
 * setup:
 *   1. set PA4 an analog mode
 *   2. enable DAC channel 1
 *   3. enable trigger
 *   4. choose software trigger as source
 *   5. update the value
 *   6. trigger DAC
 */






int main(void)
{
    float val=0.0;
    uint32_t dac_value = 0x0;
    int32_t i = 0;

    // enable GPIOA clock, bit 0 on AHB1ENR
    RCC->AHB1ENR |= (1 << 0);

    GPIOA->MODER &= ~(3<<8); // Reset bits 8-9 to clear old values
    GPIOA->MODER |= (3<<8); // Set pin 4 to analog mode (0b11)

    // enable DAC clock, bit 29 on APB1ENR
    RCC->APB1ENR |= (1 << 29);

    DAC->CR |= (1 << 0); // enable DAC channel 1
    DAC->CR &= ~(1 << 1); // enable DAC ch1 output buffer
    DAC->CR |= (1 << 2); // enable trigger
    DAC->CR |= (7 << 3); // choose sw trigger as source (0b111)

    // set output to Vref * (dac_value/0xFFF)
    DAC->DHR12R1 = dac_value;
    DAC->SWTRIGR |= (1 << 0); // trigger ch1


    while (1)
    {
    dac_value = val*(4095)/3.3;
    DAC->DHR12R1 = dac_value;
    DAC->SWTRIGR |= (1 << 0 ); // trigger ch1
    val += 0.5;
    for (i=0; i<500000; i++);
    if (val>3) val=0.2;
    }
        return 0; //unreachable code
    }
