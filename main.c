/**
 * main.c
 */

#include "msp.h"
#include "A8.h"
#include "A2.h"
#include "A7.h"

#define UPPER_BOUND 4095
#define LOWER_BOUND 0
#define ENTER_KEY 0x0A

void main(void){

	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	set_DCO(FREQ_24_MHz);
	UART_init();
	DAC_init();

	char data = 0;
	uint16_t final_num = 0;
	int i;
	int counter = 0;
	char data_array[4];

	for(i = 0; i < 4; i++){   //initialize array
	    data_array[i] = '\0';
	}

	while(1){
	    if(get_receive_flag()){ // flag found
	        data = receive_data(); // receiving data

	        delay_us(5000);        // transmitting data back
	        transmit_data(data);   // so we can see it on
	        delay_us(50000);       // the putty terminal

	        if(data >= '0' && data <= '9'){  // adding values to the array
	            data_array[counter] = data;
	            counter +=1;
	        }

	        if(data == ENTER_KEY || counter >= 4){
                final_num = array_to_int(data_array);  // turn array into int
                if (final_num >= LOWER_BOUND && final_num <= UPPER_BOUND){
                    sendto_DAC(final_num);
                }
                counter = 0;             //resetting counter
                for(i = 0; i < 4; i++){  //resetting array
                    data_array[i] = '\0';
                }
            }

	        set_receive_flag(0);  // resetting flag
	        EUSCI_A0 -> IE |= EUSCI_A_IE_RXIE;   //enable receive interrupt
	    }
	}
}
