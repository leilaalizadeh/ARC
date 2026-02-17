#include "../Main.h"
#include "LPC17xx.h"
#define debounce_time 50
extern uint32_t tick;

uint32_t last_tick0 = 0;
int state0 = 1;

unsigned char* array[255]={};
int msb = 0;
extern uint32_t Recaman(unsigned char* array,uint8_t count);

	
extern volatile uint16_t ADC_current;
                
void EINT0_IRQHandler (void)	  
{
	LPC_SC->EXTINT = (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  
{                    
	LED_Out(0);                     
	if(tick<debounce_time && state0==1){
		state0=0;
		last_tick0 = tick;
    
		msb = ADC_current >> 4;    
		Recaman(array,msb); 
		uint32_t first_value = array[0];
		uint8_t lsb = (uint8_t)(first_value & 0xFF);    
		LED_Out(lsb);
		
		delay_ms(2000);
		LED_Out(0);
		
		disable_timer(0);
		init_timer_SRI(1,500000,0b011);			
		enable_timer(1);

		
		LPC_SC->EXTINT &= (1 << 0); /* clear pending interrupt         */
		return;
	}
	if ((tick - last_tick0) < debounce_time) {	
        LPC_SC->EXTINT &= (1 << 1); /* clear pending interrupt         */
        return;
	}
	last_tick0 = tick;
	state0=1;
	
	msb = ADC_current >> 4;    
	Recaman(array,msb); 
	uint32_t first_value = array[0];
	uint8_t lsb = (uint8_t)(first_value & 0xFF);    
	LED_Out(lsb);
	
  init_timer_SRI(1,500000,0b011);			
	enable_timer(1);                      
	LPC_SC->EXTINT = (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  
{
  LPC_SC->EXTINT = (1 << 2);     /* clear pending interrupt         */    
}


