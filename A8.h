/*
 * A8.h
 *
 *  Created on: May 15, 2020
 *      Author: Melina Lopez
 */

#ifndef A8_H_
#define A8_H_

#define RBIT BIT3
#define TBIT BIT2

void UART_init();
uint8_t receive_data();
void transmit_data(uint16_t data);
void set_receive_flag(uint8_t val);
uint8_t get_receive_flag();
void EUSCIA0_IRQHandler();
uint16_t array_to_int(char data_array[]);


#endif /* A8_H_ */
