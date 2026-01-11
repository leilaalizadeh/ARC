OUTPUT			RN 0
COUNT			RN 1
N				RN 2
SWAPPED			RN 3
CNT				RN 4
TMP				RN 5
TMP1			RN 6
INDEX			RN 7

				AREA MY_CODE,CODE,READONLY
copyData		PROC
				EXPORT copyData
				PUSH{R4-R8,R10-R11,LR}
				LDR R3,=0
FOR	
				CMP R3,R2
				BEQ FINISH
				LDRSB R4,[R0,R3]
				STRB  R4,[R1,R3]
				ADD R3,#1
				B FOR
FINISH
				POP{R4-R8,R10-R11,PC}
				ENDP
					
bubbleSort		PROC
				EXPORT bubbleSort
				PUSH{R4-R8,R10-R11,LR}
				
				MOV N,COUNT      ; N = LENGTH(A)
				LDR SWAPPED,=1   ; swapped = TRUE
				
WHILE
				CMP SWAPPED,#1
				BNE FINISH1
				
				CMP N,#1
				BLS	FINISH1     
				
				; while swapped and n > 1
				
				LDR SWAPPED,=0   ; swapped = false
				
				LDR CNT,=1       ; I = 1
FOR1				
				CMP CNT,N
				BEQ	NEXT_WHILE
				
				; for i = 1 to n - 1
				
				LDRSB TMP,[OUTPUT,CNT]    ; A[I]
				
				SUB INDEX, CNT,#1         ; I - 1
				
				LDRSB TMP1,[OUTPUT,INDEX] ; A[I-1]
				
IF_				
				CMP TMP1,TMP              ; if A[i - 1] > A[i] 
				BLE ELSE_IF
										  ; then
				STRB TMP,[OUTPUT,INDEX]   ; swap(A[i - 1], A[i]) 
                STRB TMP1,[OUTPUT,CNT]				
				LDR SWAPPED,=1            ; swapped = true
				
				ADD CNT,#1
				B FOR1
					

ELSE_IF	
				ADD CNT,#1
				B FOR1
NEXT_WHILE	
				SUB N,#1
				B WHILE
FINISH1
				POP{R4-R8,R10-R11,PC}
				ENDP
				END
					
					