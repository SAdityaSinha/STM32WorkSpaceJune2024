#pragma once


#include "stm32f446xx.h"

void adc_init();
void adc_int_init();
void adc_start_conversion();
uint32_t adc_read();
