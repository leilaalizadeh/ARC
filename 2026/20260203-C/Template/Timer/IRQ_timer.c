/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "../Main.h"
extern uint32_t tick;

extern volatile uint16_t ADC_current;
volatile uint16_t prev_adc = 0;

extern unsigned char* array[];
extern int msb;
int count= 1;

int flag = 0;


void TIMER0_IRQHandler (void)
{
	if (prev_adc != ADC_current){              
		LED_Out(0);                              
		prev_adc = ADC_current;                  
		int msb = ADC_current >> 4;               
		for(int i=0;i<8;i++){                   
			int led = 11-(4+i);                    
			int bit = msb >> (7-i);                
			int val = bit & 1 ;                    
			if(val == 1)                           
				LED_On(led);                    
		}
	}
  LPC_TIM0->IR |= 1;			/* clear interrupt flag */
  return;
}


void TIMER1_IRQHandler (void)
{
	if(flag == 0){
		flag = 1;
		if(count != msb){
			count++;
			uint8_t value = array[count];
			uint8_t lsb = (uint8_t)(value & 0xFF); 
			for(int i=0;i<8;i++){                   
				int led = 11-(4+i);                    
				int bit = lsb >> (7-i);                
				int val = bit & 1 ;                    
				if(val == 1)                           
					LED_On(led);                    
		  } 
		}
		else{
			disable_timer(1);
			init_timer_SRI(0,1250000,0b011);			//stop reset interrupt
		  enable_timer(0);
			count = 0;
		}
	
	}
	else{
		flag = 0;
		LED_Out(0);
		
	}
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER2_IRQHandler (void)
{
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER3_IRQHandler (void)
{
	tick++;
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
