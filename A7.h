/*
 * A7.h
 */

#ifndef A7_H_
#define A7_H_

#include "msp.h"
#include <math.h>

#define THREEV 3724 //4096/3.3 *3
#define ONEHALFV 1862
#define NOTCS BIT1
#define SCLK BIT6
#define MOSI BIT5
#define GAIN BIT5
#define SHDN BIT4
#define INCREMENT 10
#define SINETABLESIZE 1000

extern volatile uint16_t volts_list[SINETABLESIZE];

void sine_list_maker();
void sawtooth(uint16_t current_freq);
void sine(uint16_t current_freq);
void triangle();
void square();
void DAC_init();
void sendto_DAC(uint16_t data);

#endif /* A7_H_ */
