/*
 * my_Serial.h
 *
 *  Created on: Jul 24, 2024
 *      Author: sinha
 */

#ifndef INC_MY_SERIAL_H_
#define INC_MY_SERIAL_H_


void rx_init();
void rx_interrupt_init();
char rx_read();

void tx_init();
void tx_send(char c);


#endif /* INC_MY_SERIAL_H_ */
