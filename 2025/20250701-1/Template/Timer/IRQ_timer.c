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

extern int num_correct;
extern int num_wrong;

extern int nextElementLCG(int seed, int a, int c, int n, int m);

int counter =0;
int seed = 1;

int flag = 0;
int answered = 0;

void start_next_step(void)
{
    if(counter < 10){
        answered = 0;

        seed = nextElementLCG(seed, 131, 7, counter, 255);
				int mod = seed % 4;
        LED_Out(0);

        if(mod == 0){ 
					LED_On(11-11); 
					flag = 0; 
				}      // UP
        else if(mod == 1){ 
					LED_On(11-10); 
					flag = 1; 
				} // LEFT
        else if(mod == 2){ 
					LED_On(11-9);  
					flag = 2; 
				} // RIGHT
        else {                
					LED_On(11-8);
					flag = 3;
				}      // DOWN
    }
    else{
        LED_Out(0);
        if(num_correct > num_wrong) LED_On(11-4);  // Victory
        else                        LED_On(11-5);  // Defeat
    }
}

void TIMER0_IRQHandler (void)
{
	if(counter < 10){
        if(answered == 0){
            num_wrong++;
            counter++;
            start_next_step();   
        }
    }else{
        LED_Out(0);
        if(num_correct > num_wrong) 
					LED_On(11-4);
        else                        
					LED_On(11-5);
   }
	
	
	
	
	
//	if(counter < 10){
//		LED_Out(0);
//		flag = 1;
//		seed = nextElementLCG(seed,131,7,counter,255);
//		int mod = seed % 4;
//		if(mod == 0) 
//			LED_On(11-11);
//		else if(mod == 1) 
//			LED_On(11-10);
//		else if(mod == 2) 
//			LED_On(11-9);
//		else if(mod == 3) 
//			LED_On(11-8);
//		else LED_Out(0);
//		counter++;
//	}
//	else{
//		LED_Out(0);
//		if(num_correct > num_wrong)
//			LED_On(11-4);
//		else 
//			LED_On(11-5);
//	}
  LPC_TIM0->IR |= 1;			/* clear interrupt flag */
  return;
}


void TIMER1_IRQHandler (void)
{
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
