M_A		        RN 0
M_B		        RN 1
I				RN 2
J				RN 3
X				RN 4
B				RN 5
TMP				RN 6
INDEX			RN 7
RESULT			RN 8


						AREA MY_CODE, CODE, READONLY
transposition           PROC
	                    EXPORT transposition
					    PUSH{R4-R8,R10-R11,LR}
						LDR I,=0
						
WHILE
						CMP I,#8
						BEQ FINISH
						
						LDR RESULT,=0
						LDR J,=0
FOR		
						CMP J,#8
						BEQ NEXT
						
						LDRB X,[M_A,J]
						
						LDR INDEX,=7
						SUB INDEX,I
						
						LSR TMP,X,INDEX
						
						AND TMP,#1
						
						LDR INDEX,=7
						SUB INDEX,J
						
						LSL TMP,INDEX
						
						ORR RESULT,TMP
						
						ADD J,#1
						B FOR 
						
NEXT
                        STRB RESULT,[M_B,I]
						ADD I,#1
						B WHILE
						
FINISH
						MOV R0, M_B
						POP{R4-R8,R10-R11,PC}
						ENDP
						END