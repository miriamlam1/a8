/* a7.c: DAC converter
UCB0SIMO = P1.6
UCB0CLK = P1.5
P4.1
*/
#include "msp.h"
#include "A7.h"

void DAC_init(){
    P4->SEL0 &= ~NOTCS; // pin 4.1 GPIO
    P4->SEL1 &= ~NOTCS;
    P4->OUT |= NOTCS;   //initialize high bec CS is active low
    P4->DIR |= NOTCS;   // pin 4.1 is output

    P1->SEL0 |= (MOSI|SCLK);
    P1->SEL1 &= ~(MOSI|SCLK); // set to primary mode (SPI)

    EUSCI_B0 -> CTLW0 |= (EUSCI_B_CTLW0_SWRST | // software reset enabled
            EUSCI_B_CTLW0_MST | // master mode
            EUSCI_B_CTLW0_SYNC| // MSB first when transmitting
            EUSCI_B_CTLW0_MSB | // synchronous mode
            EUSCI_B_CTLW0_CKPL| // polarity: inactive state is high
            EUSCI_B_CTLW0_UCSSEL_2); // clock source: SMCLK

    //EUSCI_B0->BRW = 0x02;              // div by 2 fBitClock = fBRCLK / UCBRx
    EUSCI_B0 -> CTLW0 &= ~EUSCI_B_CTLW0_SWRST; // software reset disabled
}

void sendto_DAC(uint16_t data){
    uint8_t top8 = 0x0F & (data >> 8);
    uint8_t lower8 = data & 0xFF;
    top8 |= (GAIN | SHDN);

    P4->OUT &= ~(NOTCS); //set CS bit low

    while (EUSCI_B0 -> IFG & EUSCI_B_IFG_TXIFG == 0);  //wait
    EUSCI_B0 -> TXBUF = top8; //transmit top8
    while (EUSCI_B0 -> IFG & EUSCI_B_IFG_TXIFG == 0);  //wait
    EUSCI_B0 -> TXBUF = lower8;
    while(EUSCI_B0 -> IFG & EUSCI_B_IFG_RXIFG == 0); //RXIFG is set when UCxxRXBUF has received a complete character

    P4->OUT |= (NOTCS); //set CS bit high
}
