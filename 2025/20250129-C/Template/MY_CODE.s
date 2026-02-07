M_A		        RN 0
M_B		        RN 1
I				RN 2
J				RN 3
X				RN 4
TMP				RN 5
INDEX			RN 6
RESULT			RN 7


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
						
; FIRST COL OF A IS FIRST ROW OF AT - J=0 => BIT7 OF ALL ITEMS IN X => FIRST ROW OF AT
FOR		
						CMP J,#8
						BEQ NEXT
						
						LDRB X,[M_A,J]   ; X = MARIX_A[J] - 0xF8, 0x7C, 0x3E, 0x1F, 0x8F, 0xC7, 0xE3, 0xF1
						
						LDR INDEX,=7
						SUB INDEX,I
						
						LSR TMP,X,INDEX   ; BIT7,6,5,4,3,2,1 X
						
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
						POP{R4-R8,R10-R11,PC}
						ENDP
						END