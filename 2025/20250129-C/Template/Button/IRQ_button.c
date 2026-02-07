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

int count = 0;
int count1 = 0;

uint8_t A[8] = {};
uint8_t B[8] = {};
uint8_t C[8] = {};
uint8_t Ct[8] = {};
uint8_t At[8] = {};
uint8_t Bt[8] = {};
extern void transposition(uint8_t* array_a,uint8_t* array_b);
	
static int equal(const uint8_t x[8], const uint8_t y[8]) {
  for (int i = 0; i < 8; i++) {
    if (x[i] != y[i]) return 0;
  }
  return 1;
}	

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

	if(count ==8 && count1 == 8){
		for (int i=0; i < 8; i++){
			C[i] = A[i] + B[i];
		}
		
		transposition(C,Ct);
		transposition(A,At);
		transposition(B,Bt);
		
		for (int i; i<8; i++){
			C[i] = At[i] + Bt[i];
		}
		
		if(equal(Ct , C)){
			LED_Out(0);
			LED_On(4);
		}
		else{
			LED_Out(0);
			LED_On(6);
		}
	}
		
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


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
		A[count] = (uint8_t)time;
		count ++;
	}
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}
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
		B[count1] = (uint8_t)time;
		count1 ++;
	}
		
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


