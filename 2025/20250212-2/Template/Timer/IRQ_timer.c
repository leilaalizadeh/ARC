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
extern signed int Maclaurin(int y, int n);
int cosineValues[45];
static int repeat = 0;
static int ticks = 0;

static int cast_to_int(float input){
		if (input > 0)
			input = input + 0.5f;
		else
			input = input - 0.5f;
		return (int)input;
}

void TIMER0_IRQHandler (void)
{
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


void TIMER1_IRQHandler (void)
{
	int input, output;
	if (repeat < 200)
	{
		input =cast_to_int(1.428 * ticks); // see Note 1 below	
		output = 500 + Maclaurin(input, 3) / 2;
		cosineValues[ticks + 22] = output; // see Note 2 below
		DAC_write(output);
		ticks ++;
		if (ticks > 22)
		{
			ticks = -22;
			repeat += 1;
		}
	}
	else
		DAC_write(0);
	
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
