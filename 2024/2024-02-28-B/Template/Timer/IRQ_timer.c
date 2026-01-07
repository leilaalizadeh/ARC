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
extern char Maze[9][8];
extern int ROW_NUM;
extern int COL_NUM;
extern int x;
extern int y;

void TIMER0_IRQHandler (void)
{
	LED_Out(0);
	int flag = 1;
		while(flag){
			  int i,j;
			  char val  = ' ';
			  //top
   			i = x - 1; 
			  j = y;
     		val = Maze[i][j];
			  if (val == ' '){
					x = i;
					y = j;
					Maze[x][y] = 'X';
					LED_On(11);
					continue;
				}
			//right
				i = x; 
			  j = y + 1;
     		val = Maze[i][j];
			  if (val == ' '){
					x = i;
					y = j;
					Maze[x][y] = 'X';
					LED_On(8);
					continue;
				}
			//left
				i = x; 
			  j = y-1;
     		val = Maze[i][j];
			  if (val == ' '){
					x = i;
					y = j;
					Maze[x][y] = 'X';
					LED_On(10);
					continue;
				}
			//bottom
			  i = x + 1; 
			  j = y;
     		val = Maze[i][j];
			  if (val == ' '){
					x = i;
					y = j;
					Maze[x][y] = 'X';
					LED_On(9);
					continue;
				}
				else
					break;
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
