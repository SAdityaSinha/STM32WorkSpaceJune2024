#include <stdint.h>

#include<stdio.h>

//#include "sysTick.h"
#include "adc.h"
//#include "sysTick.c"

#include "pll.h"
#include "serial.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif



int main(){

    clockSpeed_PLL();

    tx_init();
    adc_init();
    adc_int_init();

    adc_start_conversion();

    while(1){

    };
}

int __io_putchar(int ch){
    tx_send(ch);
    for(uint32_t i=0;i<500000;i++);
    return ch;
}
