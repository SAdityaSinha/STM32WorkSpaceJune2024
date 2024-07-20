/*
 * passVerifier.h
 *
 *  Created on: Jul 15, 2024
 *      Author: sinha
 */

#ifndef INC_PASSVERIFIER_H_
#define INC_PASSVERIFIER_H_

#include<stdbool.h>
// #include

void normalDelay(int delayAmount);

void blinkLedXtime(int times);      //define in main()

bool isButton2Pressed(bool arePortsSet, bool buttonStatus);

bool updateOnButtonRelease(int *passCode,bool *passVerifier,short int inputDetected);

void setAllVerifierNULL(bool *passVerifier);




#endif /* INC_PASSVERIFIER_H_ */
