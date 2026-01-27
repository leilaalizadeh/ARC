/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "RIT.h"
#include "../Main.h"
/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

int num_correct = 0;
int num_wrong = 0;
extern int flag;
extern int seed;
extern int counter;


void RIT_IRQHandler (void)
{	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){			//sel
	}	
	else if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){			//down 8
		if(flag==1){
			flag=0;
			if((seed%4)==3)
				num_correct++;
			else 
				num_wrong++;
			LED_Out(0);
		}
	}else if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){			//left 10
		if(flag==1){
			flag=0;
			if((seed%4)==1)
				num_correct++;
			else 
				num_wrong++;
			LED_Out(0);
		}
	}else if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){			//right 9
		if(flag==1){
			flag=0;
			if((seed%4)==2)
				num_correct++;
			else 
				num_wrong++;
			LED_Out(0);
		}
	}else if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){			//up 11
		if(flag==1){
   		flag=0;
			if((seed%4)==0)
				num_correct++;
			else 
				num_wrong++;
			LED_Out(0);
		}
	}
	reset_RIT();
		
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
}
		

/******************************************************************************
**                            End Of File
******************************************************************************/
