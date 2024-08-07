/*
 * blinkLED.c
 *
 *  Created on: Jul 13, 2024
 *      Author: sinha
 */
#include"blinkLED.h"
//#include<stdio.h>

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
//		printf("bool true\n");
		return true;
	}
//	printf("bool false\n");

	return false;
}

void setAllVerifierNULL(bool *passVerifier)
{
	passVerifier[0] =false;
	passVerifier[1] =false;
	passVerifier[2] =false;
	passVerifier[3] =false;
}



bool updateOnButtonRelease(int *passCode,bool *passVerifier,short int inputDetected)
{
	//is onTime signal is short or long
	// short int inputDetected;
	// if(OnTime>0 && OnTime<=3)
	// {
	// 	inputDetected = 0;
		
	// }else if(OnTime>3)
	// {
	// 	inputDetected = 1;
	// }
	// unsigned int counter:4;		//IDK why bitField is not working 
	int counter = 0;
	if(passVerifier[0])
	{
		counter++;
		if(passVerifier[1])
		{
			counter++;
			if(passVerifier[2])
			{
				counter++;
				if(passVerifier[3])
				{
					//this block is never gonna run
					return true;
				}else
				{
					//checking for pos-4 ind-3
					if(inputDetected==passCode[counter])
					{
						passVerifier[counter] =true;
						return true;
					}else
					{
						//set all passVerifier as false
						setAllVerifierNULL(passVerifier);
					}
				}
			}else
			{
				//pass 0 and 1 is true now for 2(indx)
				if(inputDetected==passCode[counter])
				{
					passVerifier[counter] =true;
					return false;
				}else
				{
					//setting all to NULL
					setAllVerifierNULL(passVerifier);
				}
			}
		}else
		{
			if(inputDetected==passCode[counter])
			{
				passVerifier[counter] = true;
				return false;
			}else
			{
				//setting all as NULL
				setAllVerifierNULL(passVerifier);
			}
		}
	}else
	{
		if(inputDetected==passCode[counter])
			{
				passVerifier[counter] = true;
				return false;
			}else
			{
				//setting all as NULL
				setAllVerifierNULL(passVerifier);
			}	
	}

	return false;

}



