#include "Main.h"


extern volatile uint16_t ADC_current;

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
		LED_Out(0);
		int msb = ADC_current >> 4;   
		for(int i=0;i<8;i++){
	 	  LED_Out(0);
			int led = 11-(4+i);
			int bit = msb >> (7-i); 
			int val = bit & 1 ;
			if(val == 1)
				LED_On(led); 
   }
	}
}