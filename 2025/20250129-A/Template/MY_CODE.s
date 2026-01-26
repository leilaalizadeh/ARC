MATRIX					RN 0
B_MATRIX				RN 1
C_MATRIX				RN 2
CNT 					RN 3
CURRENT				    RN 4
VAL 					RN 5
VAL1					RN 6
VAL2					RN 7
CNT1					RN 8
RESULT					RN 9
MASK					RN 10

						AREA MY_CODE, CODE, READONLY

bitwiseAffineTransformation	PROC
							EXPORT bitwiseAffineTransformation
							PUSH{R4-R8,R10-R11,LR}
							
						    LDR CNT,=0
							LDR RESULT,=0 ; 0000 0000
FOR
							CMP CNT,#8
							BEQ FINISH
							
							LDRB CURRENT, [MATRIX,CNT] ; A = 0xF8, 0x7C, 0x3E, 0x1F, 0x8F, 0xC7, 0xE3, 0xF1
							AND	 VAL,CURRENT,B_MATRIX  ; STEP 1: 0xF8 AND 0xAA   A0 AND B
							
							;STEP2
							LDR CNT1,=1
							AND VAL2,VAL,#1	; BIT0
FOR1
							CMP CNT1,#8
							BEQ NEXT2 
							
							LDR MASK,=1          ; 0000 0001
							LSL MASK,CNT1        ; 0000 0010
							AND VAL1,VAL,MASK    ; VALUE BIT1 
							LSR VAL1,CNT1        ; 0000 0001
							EOR	VAL2,VAL1        ; V = BIT0 XOR BIT1 ,  V = V XOR BIT2, V = V XOR BIT3, ...
							ADD CNT1,#1
							B FOR1 
							
NEXT2						
							;STEP3
                            LDR MASK,=7           
							SUB MASK,MASK,CNT     ; 7-0, 7-1, 7-2,...
							LSR VAL,C_MATRIX,MASK ; BIT0 C_MATRIX
							AND VAL,#1
							EOR VAL2,VAL,VAL2     ; 0000 0001
							
							LSL VAL2,MASK         ; 0100  0000
							ORR RESULT, VAL2      ; 1100  0000
							
							ADD CNT,#1
							B FOR
							
FINISH
							MOV R0,RESULT
							
							POP{R4-R8,R10-R11,PC}
							ENDP
						END