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

unsigned char matrix_a[8];
unsigned char matrix_b[8];
unsigned char matrix_c[8];	
	
int count = 0;
	
extern unsigned char* bitMatrixMultiplication(unsigned char* A,unsigned char* B,unsigned char* C);
	
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
	if(count < 8){
		uint32_t time = read_timer(1);
		uint32_t lsb = time & 0xFF;
		uint32_t msb = time >> 8;
		msb = msb & 0xFF;
		matrix_a[count] = lsb;
		matrix_b[count] = msb;
		count ++;
	}
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
	if(count == 8){
		bitMatrixMultiplication(matrix_a,matrix_b,matrix_c);
	}
	init_timer_SRI(0,125000,0b011);			//stop reset interrupt
	enable_timer(0);
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


