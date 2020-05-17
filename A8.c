/*
 * A8.c
 *
 * UART - universal asynchronous receiver transmitter
 *
 */
#include "msp.h"
#include "A8.h"
#include <math.h>

uint8_t receive = 0;

void UART_init(){
    //UART port and pins
    P1 -> SEL0 |=  (TBIT | RBIT); //check this
    P1 -> SEL1 &= ~(TBIT | RBIT);

    //USCI_A0
    EUSCI_A0 -> CTLW0 |= EUSCI_A_CTLW0_SWRST;    //SWRT enabled
    EUSCI_A0 -> CTLW0 |= EUSCI_A_CTLW0_UCSSEL_2; //SMCLK
    EUSCI_A0 -> CTLW0 &= ~EUSCI_A_CTLW0_MODE_0;  //UART mode
    EUSCI_A0 -> BRW = 2500; //SMCLK = 24MHz / baud rate = (9600)
    EUSCI_A0 -> MCTLW &= ~EUSCI_A_MCTLW_OS16; //oversampling mode disabled
    EUSCI_A0 -> CTLW0 &= ~EUSCI_A_CTLW0_SWRST;    //SWRT disabled
    EUSCI_A0 -> IE |= EUSCI_A_IE_RXIE;   //enable receive interrupt
    NVIC -> ISER[0] = 1 << (EUSCIA0_IRQn & 31); //set NVIC interrupt

    __enable_irq(); //enabled global interrupts
}

uint8_t receive_data(){
    uint8_t data = 0;
    while(EUSCI_A0 -> IFG & EUSCI_A_IFG_RXIFG == 0); //wait for input buffer to fill
    data = (EUSCI_A0 -> RXBUF);    //last recieved char
    return data;
}

void transmit_data(uint16_t data){
    while(EUSCI_A0 -> IFG & EUSCI_A_IFG_TXIFG == 0); //wait for buffer to be empty
    EUSCI_A0 -> TXBUF = data;
    while(EUSCI_A0 -> IFG & EUSCI_A_IFG_TXIFG == 0); //wait for buffer to be empty
}

void set_receive_flag(uint8_t val){
    receive = val;
}

uint8_t get_receive_flag(){
    return receive;
}

void EUSCIA0_IRQHandler(){
    EUSCI_A0 -> IE &= ~EUSCI_A_IE_RXIE;   //enable receive interrupt
    receive = 1;
}

uint16_t array_to_int(char data_array[]){ // 1 2 3 4
    uint16_t num = 0;
    int i;
    for(i = 0; i < 4; i++){
        if (data_array[i]!= '\0'){
            num *=10;
            num += (data_array[i]-48);
        }
    }
    return num;
}


