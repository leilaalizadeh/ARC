#include "LPC17xx.h"
void DAC_init(void){
	LPC_PINCON->PINSEL1 |= (1<<21);
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);		
}

void DAC_write(uint16_t value){
	LPC_DAC->DACR = value<<6;
}