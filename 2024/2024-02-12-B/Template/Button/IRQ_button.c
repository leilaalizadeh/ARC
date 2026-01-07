#include "../Main.h"
#include "LPC17xx.h"
#define debounce_time 50
extern uint32_t tick;
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
int visited[200];
extern exploreMaze(int row,int col,char *MAZE, int visited[]);
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
	
		uint32_t time = read_timer(0);
		int v = (time * 11 + 6) % 73;	

		int all = NUM_ROWS * NUM_COLUMNS;
		for (int r = 1; r < NUM_ROWS - 1; r++) {
				for (int c = 1; c < NUM_COLUMNS - 1; c++) {
					if ((r == 1 && c == 1) ||(r == NUM_ROWS - 2 && c == NUM_COLUMNS - 2))
						continue;
					int idx = r * NUM_COLUMNS + c;
					Maze[idx] = (v < 40) ? ' ' : 'X';
					v = (v * 11 + 6) % 73;
				}
	   }
     for (int i=0;i<NUM_COLUMNS;i++) //top
				Maze[i] = 'X';
		 for (int i= all-1;i >= ((NUM_ROWS - 1) * NUM_COLUMNS) ;i--) //bottom
				Maze[i] = 'X';
		 for(int i=((NUM_COLUMNS-1)+NUM_COLUMNS);i<=(NUM_ROWS*NUM_COLUMNS)-1;i+=NUM_COLUMNS) // right 
		    Maze[i]='X';
		 for (int i=0; i<all; i = i + NUM_COLUMNS) // left
		    Maze[i] = 'X';

    Maze[NUM_COLUMNS + 1] = ' ';
		Maze[(all-NUM_COLUMNS)-2]= ' ';
		 
		 
		 int result = exploreMaze(NUM_ROWS,NUM_COLUMNS,Maze,visited);
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
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


