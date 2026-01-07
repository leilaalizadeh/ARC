#include "../Main.h"
#include "LPC17xx.h"
//#define debounce_time 50
//extern uint32_t tick;
//key0
//uint32_t last_tick0 = 0;
//int state0 = 1;
//key1
//uint32_t last_tick1 = 0;
//int state1 = 1;
//key2
//uint32_t last_tick2 = 0;
//int state2 = 1;

#define NUM_ROWS 10
#define NUM_COLUMNS 8

char Maze[NUM_ROWS*NUM_COLUMNS];

extern int mazeSolver(int rows,int cols,char *Maze);



void EINT0_IRQHandler (void)	  
{
//	if(tick<debounce_time && state0==1){
//		state0=0;
//		last_tick0 = tick;
////  write a copy of your code also here for debouncing
//		LPC_SC->EXTINT &= (1 << 0); /* clear pending interrupt         */
//		return;
//	}
//	if ((tick - last_tick0) < debounce_time) {	
//        LPC_SC->EXTINT &= (1 << 0); /* clear pending interrupt         */
//        return;
//	}
//	last_tick0 = tick;
//	state0=1;
////  write code from here with or without debouncing
	
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  
{
//	if(tick<debounce_time && state1==1){
//		state1=0;
//		last_tick1 = tick;
////    write a copy of your code also here for debouncing
//		LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
//		return;
//	}
//	if ((tick - last_tick1) < debounce_time) {	
//        LPC_SC->EXTINT &= (1 << 1); /* clear pending interrupt         */
//        return;
//	}
//	last_tick1 = tick;
////  write code from here with or without debouncing
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  
{
//	if(tick<debounce_time && state2==1){
//		state2=0;
//		last_tick2 = tick;
////    write a copy of your code also here for debouncing
//		LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */
//		return;
//	}
//	if ((tick - last_tick2) < debounce_time) {	
//        LPC_SC->EXTINT &= (1 << 2); /* clear pending interrupt         */
//        return;
//	}
//	last_tick2 = tick;
////  write code from here with or without debouncing
	
		uint32_t timer_value = read_timer(0);
	
		uint32_t value_new = (timer_value * 18) % 101;
	
	  int all  = NUM_ROWS * NUM_COLUMNS;
	
    for(int i=0 ; i< all; i++){
			if(i < NUM_COLUMNS){ //top border
				if(value_new < 90 ) 
					Maze[i] = '*';
				else 
					Maze[i] = 'n';
			}
			else if( i > (NUM_ROWS -1 ) * NUM_COLUMNS){ //bottom border 
				if(value_new < 90 )
					Maze[i] = '*';
				else 
					Maze[i] = 's';
			}
			else if((i % NUM_COLUMNS) == 0){ //left border 
				if(value_new < 90 ) 
					Maze[i] = '*';
				else 
					Maze[i] = 'w';
			}
			else if( ((i+1) % NUM_COLUMNS ) == 0){ //right border 
				if(value_new < 90 ) 
					Maze[i] = '*';
				else 
					Maze[i] = 'e';
			}
			else{
				if(value_new<60)
					Maze[i]=' ';
				else
					Maze[i]='*';				
			}
			value_new = (value_new * 18) % 101;
		}
		Maze[0] = '*';
	  Maze[NUM_COLUMNS - 1] = '*';
	  Maze[(NUM_ROWS * NUM_COLUMNS)-NUM_COLUMNS] = '*';
		Maze[(NUM_ROWS * NUM_COLUMNS)-1] = '*';
	  int result = mazeSolver(NUM_ROWS,NUM_COLUMNS,Maze);
		
		
    LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


