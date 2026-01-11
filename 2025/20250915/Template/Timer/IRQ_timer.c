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

extern int flag;
extern int var;
int so = 0;


 uint16_t SinTable[45] =                                       
 {
     410, 467, 523, 576, 627, 673, 714, 749, 778,
     799, 813, 819, 817, 807, 789, 764, 732, 694, 
     650, 602, 550, 495, 438, 381, 324, 270, 217,
     169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
     20 , 41 , 70 , 105, 146, 193, 243, 297, 353
 };

void TIMER0_IRQHandler (void)
{
	if (so == 0){
		if(flag == 1){
			flag = 0;
			DAC_write(SinTable);
		}
		so = 1;
	}
	else{
			so = 0;
			LED_Out(0);
			flag = 0;
		  var = 0;
			disable_timer(0);
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
