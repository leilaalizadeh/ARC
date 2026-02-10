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
		init_timer_SRI(3,25000,0b011);			//EDITED: ADD - DEBOUNCING
		enable_timer(3);                    //EDITED: ADD - DEBOUNCING
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
			__WFI();                                     // EDITED:  ADD – WAKE UP ONLY WHEN AM INTERRUPT  HAPPENS
			if(change){                                  // EDITED:  ADD – SET TO 1 IN IRQ
				change = 0;                                // EDITED:  ADD 
				if (prev_adc != ADC_current){              // EDITED:  ADD 
					LED_Out(0);                              // EDITED:  ADD 
					prev_adc = ADC_current;                  // EDITED:  ADD 
					int msb = ADC_current >> 4;              // EDITED:  CHANGE 8 TO 4 
					for(int i=0;i<8;i++){                    // EDITED:  ADD
						int led = 11-(4+i);                    // EDITED:  ADD
						int bit = msb >> (7-i);                // EDITED:  ADD
						int val = bit & 1 ;                    // EDITED:  ADD
						if(val == 1)                           // EDITED:  ADD
									 LED_On(led);                    // EDITED:  ADD
					}
				}
			}
	}
}