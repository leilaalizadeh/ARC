INPUT			RN 0
OUTPUT 			RN 1
COUNT 			RN 2
CNT				RN 3
TMP				RN 4

				AREA MY_CODE,CODE,READONLY
copyData 		PROC
				EXPORT copyData	
				PUSH{R4-R8,R10-R11,LR}

				LDR CNT,=0
FOR
				CMP COUNT,CNT
				BEQ FINISH
				
				LDRSB TMP,[INPUT,CNT]
				STRB TMP,[OUTPUT,CNT]
				
				ADD CNT,#1
				B FOR		
FINISH
				POP{R4-R8,R10-R11,PC}
				ENDP
					
					
insertionSort 	PROC
				EXPORT insertionSort	
				PUSH{R4-R8,R10-R11,LR}
				;R0 OUTPUT
				;R1 LENGTH(A)
                LDR R2,=1 ;  I 

WHILE
				CMP R2,R1  ; I,COUNT  - I < LENGTH(A)
				BHS NEXT_1 ; I >= LENGTH(A)
				
				LDRSB R3,[R0,R2]  ; X = A[I]
				SUB  R4,R2,#1    ; J = I - 1
WHILE_2				
				CMP R4,#0    ;J >= 0
				BLT	NEXT_2   ;J < 0
				
				LDRSB R5,[R0,R4]  ;A[J]
				CMP R5,R3        ; A[J] > X
				BLE	NEXT_2       ; A[J] <= X
				 
				ADD R6,R4,#1     ; J + 1
				STRB R5,[R0,R6]  ; A[J+1] = A[J]
				SUB R4,R4,#1     ; J = J - 1
				
				B WHILE_2
NEXT_2			
				ADD R6,R4,#1     ; J + 1
				STRB R3,[R0,R6]  ; A[J+1] = X
				ADD R2,#1        ; I = I + 1
				B WHILE
NEXT_1
				POP{R4-R8,R10-R11,PC}
				ENDP


				END
