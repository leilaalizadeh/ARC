#include "../Main.h"
#include "LPC17xx.h"
#define debounce_time 50
extern uint32_t tick;
uint32_t last_tick0 = 0;
int state0 = 1;

extern void Recaman(uint32_t* area, uint8_t n);
extern volatile uint16_t ADC_current;
unsigned char* area;
void EINT0_IRQHandler (void)	  
{
	LPC_SC->EXTINT = (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  
{
	LPC_SC->EXTINT = (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  
{
	if(tick<debounce_time && state0==1){
		state0=0;
		last_tick0 = tick;
//  write a copy of your code also here for debouncing
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
	Recaman(area,msb);
	
	int lsb = area[0];

	
  LPC_SC->EXTINT = (1 << 2);     /* clear pending interrupt         */    
}


