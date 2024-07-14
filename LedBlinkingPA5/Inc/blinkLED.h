/*
 * blinkLED.h
 *
 *  Created on: Jul 13, 2024
 *      Author: sinha
 */

#ifndef BLINKLED_H_
#define BLINKLED_H_


#endif /* BLINKLED_H_ */

#include<stdint.h>
#include<stdbool.h>

void normalDelay(int delayAmount);

void blinkLedNormaly(int delayAmount);
//define blinkLedNormaly in main

bool isButton2Pressed(bool arePortsSet, bool buttonStatus);

