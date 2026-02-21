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

#define n 10


void TIMER0_IRQHandler (void)
{
	if(counter <n){
		if(flag == 0){
			 flag = 1;
			 seed = nextElementLCG(seed, 131, 7, counter, 255);
			 int mod = seed % 4;
			 LED_Out(0);
			 if(mod == 0)      // UP
					LED_On(11-11);
			 else if(mod == 1) // LEFT
					LED_On(11-10); 
			 else if(mod == 2) // RIGHT
					LED_On(11-9);  
			 else              // DOWN             
					LED_On(11-8);
			counter++; 
	 }
  }else{
    LED_Out(0);
    if(num_correct > num_wrong)
       LED_On(11-4);
    else 
       LED_On(11-5);
  }

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
