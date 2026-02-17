#include "Main.h"



int main(){
	  SystemInit();
	
	//DAC
		//DAC_init();
		//DAC_write(500);
	
	//Timer
		init_timer_SRI(0,1250000,0b011);			//stop reset interrupt
		enable_timer(0);
		//uint32_t timer_value = read_timer(0);
	
	//Delay 
		init_timer_SRI(3,25000,0b011);			//1ms delay
		enable_timer(3);
		//delay_ms(50);
	
	//Button
		BUTTON_init();
	
	//LED
		LED_init();
		//LED_On(0);
	  //LED_Off(0);
		//LED_Out(255);
	
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
		
	}
	
}