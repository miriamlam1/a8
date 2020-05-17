/*
 * A2.c
 */

#include "msp.h"
#include "A2.h"

void set_DCO(int freq){
    CS->KEY = CS_KEY_VAL; //unlock CS to access registers
    CS->CTL0 = 0; //reset CS

    switch(freq){
        case FREQ_1_5_MHz:
            CS->CTL0 = CS_CTL0_DCORSEL_0;
            break;
        case FREQ_3_MHz:
            CS->CTL0 = CS_CTL0_DCORSEL_1;
            break;
        case FREQ_6_MHz:
            CS->CTL0 = CS_CTL0_DCORSEL_2;
            break;
        case FREQ_12_MHz:
            CS->CTL0 = CS_CTL0_DCORSEL_3;
            break;
        case FREQ_24_MHz:
            CS->CTL0 = CS_CTL0_DCORSEL_4;
            break;
        default:
            CS->CTL0 = CS_CTL0_DCORSEL_1; //default 3 MHz
            break;
    }
    CS->CTL1 = CS_CTL1_SELA_2 | CS_CTL1_SELS_3 | CS_CTL1_SELM_3;
    CS->KEY = 0; //lock CS
}

/*This functions should take in the number of microseconds as an integer and provide the appropriate delay up to 50 ms.*/
void delay_us(int delay)
{
    int i, j;

    int freq = ((CS->CTL0)) >> 16;

    switch(freq)
    {
    case 0:
        freq = FREQ_1_5_MHz/10000000;
        break;
    case 1:
        freq = FREQ_3_MHz/10000000;
        break;
    case 3:
        freq = FREQ_6_MHz/10000000;
        break;
    case 4:
        freq = FREQ_12_MHz/10000000;
        break;
    }

    for(i=0; i<delay;i++)
    {
        for(j=0;j<freq;j++);
    }
}
