/*
 * blinkLED.c
 *
 *  Created on: Jul 13, 2024
 *      Author: sinha
 */
#include"blinkLED.h"
#include<stdio.h>

//#include"RCC_GPIO.h"

void normalDelay(int delayAmount)
{
	if(delayAmount==0)
	{
		delayAmount = 1; //setting the default value 
	}
	for(uint32_t i=0;i<5000*delayAmount;i++);
}

bool isButton2Pressed(bool arePortsSet,bool buttonStatus )
{

//	printf("buttonStatus : %d",num);
	if(arePortsSet && buttonStatus == 1 )
	{
		//reading the bit from button
		printf("bool true\n");
		return true;
	}
	printf("bool false\n");

	return false;
}


