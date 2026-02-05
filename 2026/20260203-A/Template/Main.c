#include "Main.h"


extern volatile uint16_t ADC_current;
volatile uint16_t prev_adc = 0;
extern volatile int change;
int main(){
	  SystemInit();
	
	//DAC
		//DAC_init();
		//DAC_write(500);
	
	//Timer
		//init_timer_SRI(0,0xFF,0b000);			//stop reset interrupt
		//enable_timer(0);
		//uint32_t timer_value = read_timer(0);
	
	//Delay 
		init_timer_SRI(3,25000,0b011);			//1ms delay
		enable_timer(3);
		//delay_ms(50);
	
	//Button
		BUTTON_init();
	
	//LED
		 LED_init();
	
	//Joystick
		//joystick_init();
		
	//RIT
		//init_RIT(0xFFF);
		//enable_RIT();
		
	//ADC
		ADC_init();
		ADC_start_conversion();
	
	//GLCD
		//LCD_Initialization();
		//LCD_Clear(Black);
		//PutChar(0,0,'a',White,Black);
		//GUI_Text(0,0,(uint8_t *)"Hello world!!",White,Black);
		
	//Touch
		//TP_Init();
		//TouchPanel_Calibrate();
		//TP_DrawPoint(display.x,display.y);
		//getDisplayPoint(&display, Read_Ads7846(), &matrix );

	while(1){
		__WFI();
		
		if(change){
			change = 0;
			if (prev_adc != ADC_current){
				LED_Out(0);
				prev_adc = ADC_current;
				int msb = ADC_current >> 4;   
//				LED_Out(msb);
				for(int i=0;i<8;i++){
					int led = 11-(4+i);
					int bit = msb >> (7-i); 
					int val = bit & 1 ;
					if(val == 1)
						LED_On(led); 
			 }
		 }
   }
	}
}