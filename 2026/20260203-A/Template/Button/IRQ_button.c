#include "../Main.h"
#include "LPC17xx.h"
#define debounce_time 50
extern uint32_t tick;

uint32_t last_tick0 = 0;
int state0 = 1;

extern uint32_t Look_and_Say(uint32_t digits);
extern volatile uint16_t ADC_current;
int enable = 0;                  // EDITED: ADD - FLAG TO DETECT A BUTTON PRESS AND DISABLE ADC UPDATES 
void EINT0_IRQHandler (void)	  
{
	enable = 1;                     // EDITED: ADD - SET TRUE
	LED_Out(0);                     // EDITED: ADD
	if(tick<debounce_time && state0==1){
		state0=0;
		last_tick0 = tick;
    
		int msb = ADC_current >> 4;    
		uint32_t result = Look_and_Say(msb); 
		uint8_t lsb = (uint8_t)(result & 0xFF);   // EDITED: ADD
		for(int i=0;i<8;i++){                     // EDITED: ADD
				int led = 11-(4+i);                   // EDITED: ADD
				int bit = lsb >> (7-i);               // EDITED: ADD
				int val = bit & 1 ;                   // EDITED: ADD
				if(val == 1)                          // EDITED: ADD
					LED_On(led);                        // EDITED: ADD
		}
		
		LPC_SC->EXTINT &= (1 << 0); /* clear pending interrupt         */
		return;
	}
	if ((tick - last_tick0) < debounce_time) {	
        LPC_SC->EXTINT &= (1 << 0); /* clear pending interrupt         */
        return;
	}
	last_tick0 = tick;
	state0=1;
	
	int msb = ADC_current >> 4;
	uint32_t result = Look_and_Say(msb);
	uint8_t lsb = (uint8_t)(result & 0xFF);    // EDITED: ADD
	for(int i=0;i<8;i++){                      // EDITED: ADD
			int led = 11-(4+i);                    // EDITED: ADD
			int bit = lsb >> (7-i);                // EDITED: ADD
			int val = bit & 1 ;                    // EDITED: ADD
			if(val == 1)                           // EDITED: ADD
				LED_On(led);                         // EDITED: ADD
  } 
	
	LPC_SC->EXTINT = (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  
{
	enable = 0;                     // EDITED: ADD - ENABLE BUTTON AND ADC UPDATES 
	LPC_SC->EXTINT = (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  
{
  LPC_SC->EXTINT = (1 << 2);     /* clear pending interrupt         */    
}


