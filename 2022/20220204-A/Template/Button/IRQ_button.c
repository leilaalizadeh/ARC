#include "../Main.h"
#include "LPC17xx.h"

#define debounce_time 50
extern uint32_t tick;

uint32_t last_tick0 = 0;
int state0 = 1;

uint32_t last_tick1 = 0;
int state1 = 1;

uint32_t last_tick2 = 0;
int state2 = 1;

volatile uint32_t value = 0;
volatile uint32_t count = 0;

extern uint32_t restoringSquareRoot(uint32_t val, int k);

void EINT0_IRQHandler (void)	  
{
	if(tick<debounce_time && state0==1){
		state0=0;
		last_tick0 = tick;
    
		uint32_t result = restoringSquareRoot(value,count);
	  LED_Out(result);
		
		LPC_SC->EXTINT &= (1 << 0); /* clear pending interrupt         */
		return;
	}
	if ((tick - last_tick0) < debounce_time) {	
        LPC_SC->EXTINT &= (1 << 0); /* clear pending interrupt         */
        return;
	}
	last_tick0 = tick;
	state0=1;
	
	uint32_t result = restoringSquareRoot(value,count);
	LED_Out(result);
	
	LPC_SC->EXTINT = (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  
{
	if(tick<debounce_time && state1==1){
		state1=0;
		last_tick1 = tick;
		
		count++;
	  value = (value << 1);
		
		LPC_SC->EXTINT &= (1 << 1); /* clear pending interrupt         */
		return;
	}
	if ((tick - last_tick1) < debounce_time) {	
        LPC_SC->EXTINT &= (1 << 1); /* clear pending interrupt         */
        return;
	}
	last_tick1 = tick;
	state1=1;
	
	count++;
	value = (value << 1);
	
	LPC_SC->EXTINT = (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  
{
	if(tick<debounce_time && state2==1){
		state2=0;
		last_tick2 = tick;

		count++;
	  value = (value << 1) | 1u;
		
		LPC_SC->EXTINT = (1 << 2); 
		return;
	}
	if ((tick - last_tick2) < debounce_time) {	
        LPC_SC->EXTINT &= (1 << 2); /* clear pending interrupt         */
        return;
	}
	last_tick2 = tick;
	state2=1;
	
	count++;
	value = (value << 1) | 1u;
	
  LPC_SC->EXTINT = (1 << 2);     /* clear pending interrupt         */    
}


