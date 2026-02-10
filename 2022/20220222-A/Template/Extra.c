//;SYSTICK
//;				LDR r0, =SYScontrolAndStatusReg
//;				MOV r1, #0
//;				STR r1, [r0]
//;				; step 1
//;				LDR r0, =SYSreloadValueReg
//;				LDR r1, =1023
//;				; example
//;				STR r1, [r0]
//;				; step 2
//;				LDR r0, =SYScurrentValueReg
//;				STR r1, [r0]
//;				; step 3
//;				LDR r0, =SYScontrolAndStatusReg
//;				MOV r1, #7
//;				STR r1, [r0]
//;				; step 4

//numIteration    DCD     0              ; 32-bit variable, initialized to 0

//SVC
//;Test bit 2 of EXC_RETURN in LR
//TST LR, #0x4
//ITE EQ
//MRSEQ r0, MSP
//MRSNE r0, PSP
//;get stacked PC from stack
//LDR r1, [r0, #24] ;see slide 10
//;get immediate from instruction
//LDRB r0, [r1, #-2]



//debouncing

//#define debounce_time 50
//extern uint32_t tick;
//key0
//uint32_t last_tick0 = 0;
//int state0 = 1;

//	if(tick<debounce_time && state0==1){
//		state0=0;
//		last_tick0 = tick;
////  write a copy of your code also here for debouncing
//		LPC_SC->EXTINT = (1 << 0); /* clear pending interrupt         */
//		return;
//	}
//	if ((tick - last_tick0) < debounce_time) {	
//        LPC_SC->EXTINT = (1 << 0); /* clear pending interrupt         */
//        return;
//	}
//	last_tick0 = tick;
//	state0=1;
////  write code from here with or without debouncing


//   LDR M,[SP,#32]  


// Button pins: P2.10(INT0), P2.11(INT1), P2.12(INT2)
// LED pins: P2.0, P2.1, P2.2, P2.3, P2.4, P2.5, P2.6, P2.7
// Joystick pins: P1.26(Down), P1.27(Left), P1.28(Right), P1.29(Up)
// ADC channel: 5
// Audio freq: const int freqs[8]={4240,3779,3367,3175,2834,2525,2249,2120};
// uint16_t SinTable[45] =                                       
// {
//     410, 467, 523, 576, 627, 673, 714, 749, 778,
//     799, 813, 819, 817, 807, 789, 764, 732, 694, 
//     650, 602, 550, 495, 438, 381, 324, 270, 217,
//     169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
//     20 , 41 , 70 , 105, 146, 193, 243, 297, 353
// };
// Simulator DARMP1.DLL		-pLPC1768
// Debugger  TARMP1.DLL		-pLPC1768
// LandTiger TARMP1.DLL		-pLPC1768 -dLandTiger


//__disable_irq();
//__enable_irq(); 


//	if(led ==0){
//		LED_On(4);
//		led =1;
//	}
//	else{
//		LED_Out(0);
//		led = 0;
//	}


//ADC
//extern volatile uint16_t ADC_current;

//uint16_t val;
//__disable_irq();			
//val = ADC_current;
//__enable_irq(); 

//base_sps = 1 + ((val * 4) / 4095);

//if (base_sps < 1) base_sps = 1;
//if (base_sps > 5) base_sps = 5;


//BRANCH
//EQ EQUAL

//MI NEGATIVE
//VS OVERFLOW

//AL	 ALWAYS

//NE 	MOT EQ

//PL POSITIVE OR 0
//VC NOT OVERFLOW


//CC/LO UNSIGNED <
//LS UNSIGNED <=
//LT SIGNED <
//LE SIGNED <=

//CS/HS UNSIGNED >=
//HI UNSIGNED >
//GE SIGNED >=
//GT	SIGNED >


//97-122 LOWERCASE
//65-90 UPPERCASE


//LSL x << 2 *
//LSR  x >> 2 /
//AND a & b
//OR a | b
//NOT ~x
//XOR ^

//reset_timer(0);
//init_timer_SRI(0,0xFFFFFFF,0b011); //1s * 25000000 - <2S
//enable_timer(0);

//reset_timer(1);
//init_timer_SRI(1,315,0b011); //1s * 25000000
//enable_timer(1);

//DAC_write(SinTable[index]);
//index++;
//if(index == 45)   //9*5
//index =0 ;
//timer 0



