MATRIX_A	    RN 0
MATRIX_B		RN 1
MATRIX_C        RN 2
I_A 			RN 3
I_B				RN 4
TMP				RN 5
TMP1			RN 6
CURRENT_A 		RN 7
CURRENT_B		RN 8
CURRENT_C		RN 9
INDEX			RN 10
RESULT			RN 11
COUNT_B         RN 12


;matrixA	DCB 0x20, 0x3F, 0xC8, 0x4D, 0x76, 0x58, 0x48, 0x50
;matrixB	DCB 0Xf8, 0x7C, 0x3E, 0x1F, 0x8F, 0xC7, 0xE3, 0xF1


				AREA MY_CODE, CODE, READONLY
					
bitMatrixMultiplication  PROC 
	                     EXPORT bitMatrixMultiplication
						 PUSH{R4-R8,R10-R11,LR}
						 
						 LDR I_A,=0
						 
FOR_A	                 ; for(I=0;I<=8;I++){
					     ;    current_A = matrix_a[CNT]
						 ;    COUNT_B = 8
						 ;    WHILE(COUNT_B <=8)
						 ;       FOR(J =0;J<=8;J++)
						 ;			
						 CMP I_A,#8
						 BEQ FINISH
						 
						 LDRB CURRENT_A,[MATRIX_A,I_A]  ;0x20, 0x3F, 0xC8, 0x4D, 0x76, 0x58, 0x48, 0x50
						 
						 LDR RESULT,=0
                         LDR COUNT_B,=0
WHILE 	
						 CMP COUNT_B,#9
						 BEQ NEXT_A
						 
						 LDR I_B,=0
						 LDR CURRENT_B,=0		
FOR_B
						 CMP I_B,#9
						 BEQ NEXT_B
						 
						 LDRB TMP,[MATRIX_B,I_B]  ; MATRIX_B[0], MATRIX_B[1], MATRIX_B[2], ...
						 LDR INDEX,=7
						 SUB INDEX,INDEX,COUNT_B
						 LSR TMP,INDEX             
						 LDR TMP1,=1
						 AND TMP1,TMP
						 
						 LDR INDEX,=7
						 SUB INDEX,INDEX,I_B
						 LSL TMP1,INDEX
						 ORR CURRENT_B,TMP1
						 ADD I_B,#1
						 B FOR_B
						 
NEXT_B
						 AND CURRENT_C, CURRENT_A,CURRENT_B
                      
						 LDR I_B,=1
						 AND TMP1,CURRENT_C,#1
						
FOR_C
						 CMP I_B,#9
						 BEQ NEXT_WHILE
						 
						 LSR TMP,CURRENT_C,I_B
						 AND TMP,#1
						 EOR TMP1,TMP
						 ADD I_B,#1
						 B FOR_C

NEXT_WHILE
						 LDR INDEX,=7
						 SUB INDEX,INDEX,COUNT_B
						 LSL TMP1,INDEX
						 ORR RESULT,TMP1
						 
                         ADD COUNT_B,#1
						 B WHILE

NEXT_A
						 STR RESULT, [MATRIX_C,I_A]
						 ADD I_A,#1
                         B FOR_A	
						 
						 
FINISH
						 MOV R0, MATRIX_C
						 
					     POP{R4-R8,R10-R11,PC}
						 ENDP
				END
					
					
					