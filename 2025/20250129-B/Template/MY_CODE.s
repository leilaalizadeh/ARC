MATRIX_A	    RN 0
MATRIX_B		RN 1
MATRIX_C        RN 2
CNT 			RN 3
CNT1			RN 4
TMP				RN 5
TMP1			RN 6
CURRENT_A 		RN 7
CURRENT_B		RN 8
CURRENT_C		RN 9
INDEX			RN 10
RESULT			RN 11
CNT3            RN 12
				
				AREA MY_CODE, CODE, READONLY
					
bitMatrixMultiplication  PROC 
	                     EXPORT bitMatrixMultiplication
						 PUSH{R4-R8,R10-R11,LR}
						 
						 LDR CNT,=0
						 
FOR_A	
						 CMP CNT,#8
						 BEQ FINISH
						 
						 LDRB CURRENT_A,[MATRIX_A,CNT]; 
						 LDR RESULT,=0
                         LDR CNT3,=0
WHILE 	
						 CMP CNT3,#9
						 BEQ NEXT_A
						 
						 LDR CNT1,=0
						 LDR CURRENT_B,=0		
FOR_B
						 CMP CNT1,#9
						 BEQ NEXT_B
						 
						 LDRB TMP,[MATRIX_B,CNT1]
						 LDR INDEX,=7
						 SUB INDEX,INDEX,CNT3
						 LSR TMP,INDEX
						 LDR TMP1,=1
						 AND TMP1,TMP
						 LDR INDEX,=7
						 SUB INDEX,INDEX,CNT1
						 LSL TMP1,INDEX
						 ORR CURRENT_B,TMP1
						 ADD CNT1,#1
						 B FOR_B
						 
NEXT_B
						 AND CURRENT_C, CURRENT_A,CURRENT_B
                      
						 LDR CNT1,=1
						 AND TMP1,CURRENT_C,#1
						
FOR_C
						 CMP CNT1,#9
						 BEQ NEXT_WHILE
						 
						 LSR TMP,CURRENT_C,CNT1
						 AND TMP,#1
						 EOR TMP1,TMP
						 ADD CNT1,#1
						 B FOR_C

NEXT_WHILE
						 LDR INDEX,=7
						 SUB INDEX,INDEX,CNT3
						 LSL TMP1,INDEX
						 ORR RESULT,TMP1
						 
                         ADD CNT3,#1
						 B WHILE

NEXT_A
						 STR RESULT, [MATRIX_C,CNT]
						 ADD CNT,#1
                         B FOR_A	
						 
						 
FINISH
						 MOV R0, MATRIX_C
						 
					     POP{R4-R8,R10-R11,PC}
						 ENDP
				END
					
					
					