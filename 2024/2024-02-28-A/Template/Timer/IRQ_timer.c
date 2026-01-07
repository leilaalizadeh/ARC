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

extern char maze[9][8];
extern i_k,j_k,k;
void TIMER0_IRQHandler (void)
{
  LPC_TIM0->IR |= 1;			/* clear interrupt flag */
	
  LED_Out(0);
	
	 if (k>=0)
	 {
			 //top
			 if((maze[i_k-1][j_k]-'0') == k){
					LED_On(4);   //led 7
				  i_k--;
			 }
			 //right
			else if((maze[i_k][j_k+1] -'0') == k){
				LED_On(7);  //led 4
				j_k++;
			}
			//left
			else if((maze[i_k][j_k-1] -'0') == k){
				LED_On(5);   //led 6
				j_k--;
			}
			//bottom
			else if((maze[i_k+1][j_k]-'0') == k){
				LED_On(6);  //led 5
				i_k++;
			}
			
			k--;
	 }
	 else{
		 //stop timer
		 //LED_Out(9);
	 }
	 
						 
				
	
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
