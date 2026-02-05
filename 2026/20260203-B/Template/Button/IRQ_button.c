#include "../Main.h"
#include "LPC17xx.h"
#define debounce_time 50
extern uint32_t tick;

uint32_t last_tick0 = 0;
int state0 = 1;

extern uint32_t Look_and_Say(uint32_t digits);
extern volatile uint16_t ADC_current;

void EINT0_IRQHandler (void)	  
{
	LED_Out(0);
	
	if(tick<debounce_time && state0==1){
		state0=0;
		last_tick0 = tick;
    
		int msb = ADC_current >> 4;
		uint32_t result = Look_and_Say(msb);
		uint8_t lsb = (uint8_t)(result & 0xFF);
		for(int i=0;i<8;i++){
				LED_Out(0);
				int led = 11-(4+i);
				int bit = lsb >> (7-i); 
				int val = bit & 1 ;
				if(val == 1)
					LED_On(led); 
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
	uint8_t lsb = (uint8_t)(result & 0xFF);
	for(int i=0;i<8;i++){
	 	  LED_Out(0);
			int led = 11-(4+i);
			int bit = lsb >> (7-i); 
			int val = bit & 1 ;
			if(val == 1)
				LED_On(led); 
  }
	LPC_SC->EXTINT = (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  
{
	LED_On(11-5);
	LPC_SC->EXTINT = (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  
{
  LPC_SC->EXTINT = (1 << 2);     /* clear pending interrupt         */    
}


