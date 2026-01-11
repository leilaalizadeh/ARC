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
extern int answered;
void start_next_step(void);

static uint32_t prevJoy = 0;
void RIT_IRQHandler (void)
{			
		uint32_t now = 0;

    if((LPC_GPIO1->FIOPIN & (1<<26)) == 0) now |= (1<<0); // down
    if((LPC_GPIO1->FIOPIN & (1<<27)) == 0) now |= (1<<1); // left
    if((LPC_GPIO1->FIOPIN & (1<<28)) == 0) now |= (1<<2); // right
    if((LPC_GPIO1->FIOPIN & (1<<29)) == 0) now |= (1<<3); // up

    uint32_t edge = now & (~prevJoy);
    prevJoy = now;

    if(counter < 10 && answered == 0)
    {
        if(edge & (1<<26)) {

						// DOWN
						if(edge & (1<<0)){
								answered = 1;
								if(flag == 3) num_correct++; else num_wrong++;
								LED_Out(0);
								counter++;
								start_next_step();
						}
						// LEFT
						else if(edge & (1<<1)){
								answered = 1;
								if(flag == 1) num_correct++; else num_wrong++;
								LED_Out(0);
								counter++;
								start_next_step();
						}
						// RIGHT 
						else if(edge & (1<<2)){
								answered = 1;
								if(flag == 2) num_correct++; else num_wrong++;
								LED_Out(0);
								counter++;
								start_next_step();
						}
						// UP
						else if(edge & (1<<3)){
								answered = 1;
								if(flag == 0) num_correct++; else num_wrong++;
								LED_Out(0);
								counter++;
								start_next_step();
						}
				}
		}

	
	
	
	
	
	
//		if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){			//sel
//		}	
//		if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){			//down
//			if(flag==3){
//				flag=0;
//				if((seed%4)==3)num_correct++;
//				else num_wrong++;
//				LED_Out(0);
//			}
//			//LED_On(11-8);
//		}
//		if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){			//left
//			if(flag==1){
//				flag=0;
//				if((seed%4)==1)num_correct++;
//				else num_wrong++;
//				LED_Out(0);
//			}
//			//LED_On(11-10);
//		}
//		if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){			//right
//			if(flag==2){
//				flag=0;
//				if((seed%4)==2)num_correct++;
//				else num_wrong++;
//			LED_Out(0);
//			}
//			//LED_On(11-9);
//		}
//		if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){			//up
//			if(flag==1){
//				flag=0;
//				if((seed%4)==0)num_correct++;
//				else num_wrong++;
//				LED_Out(0);
//			}
//			//LED_On(11-11);
//		}
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
}
		

/******************************************************************************
**                            End Of File
******************************************************************************/
