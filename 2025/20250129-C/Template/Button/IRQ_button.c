#include "../Main.h"
#include "LPC17xx.h"
#define debounce_time 50
extern uint32_t tick;
//key0
uint32_t last_tick0 = 0;
int state0 = 1;
//key1
uint32_t last_tick1 = 0;
int state1 = 1;
//key2
uint32_t last_tick2 = 0;
int state2 = 1;

unsigned char A[8] = {};
unsigned char B[8] = {};
unsigned char C[8] = {};
unsigned char D[8] = {};
extern unsigned char* transposition(unsigned char* array_a,unsigned char* array_b);
	
void EINT0_IRQHandler (void)	  
{
//	if(tick<debounce_time && state0==1){
//		state0=0;
//		last_tick0 = tick;
////  write a copy of your code also here for debouncing
//		
//		for (int i; i<8; i++){
//			C[i] = A[i] + B[i];
//		}
//	
//		unsigned char* result = transposition(C,D);
//		unsigned char* result1 = transposition(A,D);
//		unsigned char* result2 = transposition(B,D);
//	
//		for (int i; i<8; i++){
//			D[i] = result1[i] + result2[i];
//		}
//	
//		if(D == C ){
//			LED_Out(0);
//			LED_On(1);
//		}
//		else{
//			LED_Out(0);
//			LED_On(2);
//		}
//		
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

	
  for (int i=0; i < 8; i++){
		C[i] = A[i] + B[i];
	}
	
	unsigned char* result = transposition(C,D);
	unsigned char* result1 = transposition(A,D);
	unsigned char* result2 = transposition(B,D);
	
	for (int i; i<8; i++){
		D[i] = result1[i] + result2[i];
	}
	
	if(D == C ){
		LED_Out(0);
		LED_On(4);
	}
	else{
		LED_Out(0);
		LED_On(6);
	}
		
		
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}

int count = 0;
void EINT1_IRQHandler (void)	  
{
//	if(tick<debounce_time && state1==1){
//		state1=0;
//		last_tick1 = tick;
//		
//	  if(count < 8){
//			uint32_t time = read_timer(2);
//			A[count] = time;
//			count ++;
//	  }
//			
////    write a copy of your code also here for debouncing
//		LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
//		return;
//	}
//	if ((tick - last_tick1) < debounce_time) {	
//        LPC_SC->EXTINT &= (1 << 1); /* clear pending interrupt         */
//        return;
//	}
//	last_tick1 = tick;
	
	
//  write code from here with or without debouncing
	if(count < 8){
		uint32_t time = read_timer(2);
		A[count] = time;
		count ++;
	}
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}
int count1 = 0;
void EINT2_IRQHandler (void)	  
{
//		if(tick<debounce_time && state2==1){
//			state2=0;
//			last_tick2 = tick;
//	//    write a copy of your code also here for debouncing
//			
//			if(count1 < 8){
//				uint32_t time = read_timer(2);
//				B[count1] = time;
//	      count1 ++;
//			}
//				
//			LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */
//			return;
//		}
//		if ((tick - last_tick2) < debounce_time) {	
//					LPC_SC->EXTINT &= (1 << 2); /* clear pending interrupt         */
//					return;
//		}
//		last_tick2 = tick;
////  write code from here with or without debouncing
	if(count1 < 8){
		uint32_t time = read_timer(2);
		B[count1] = time;
		count1 ++;
	}
		
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


