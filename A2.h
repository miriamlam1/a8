/*
 * A2.h
 */

#ifndef A2_H_
#define A2_H_

#define DELAY100MS 300000 // DELAY * 1 mS assuming 3 MHz clock
#define FREQ_1_5_MHz 1500000
#define FREQ_3_MHz  3000000
#define FREQ_6_MHz 6000000
#define FREQ_12_MHz 12000000
#define FREQ_24_MHz 24000000
#define PORT_MCLK_OUT (P4)
#define BITM_MCLK_OUT (BIT3)

void set_DCO(int freq);

/*This functions should take in the number of microseconds as an integer
 * and provide the appropriate delay up to 50 ms.*/
void delay_us(int delay);

#endif /* A2_H_ */
