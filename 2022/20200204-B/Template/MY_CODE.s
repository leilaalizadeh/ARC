X			RN 0
K			RN 1
R			RN 2
P			RN 3
Q			RN 4
I			RN 5
TMP			RN 6
ONE	     	RN 7
TMP1		RN 8
INDEX       RN 10

			AREA MY_CODE,CODE, READONLY
				
nonRestoringSquareRoot	PROC
			EXPORT nonRestoringSquareRoot
			PUSH{R4-R8,R10-R11,LR}
			
			LDR ONE,=1
				
			MOV R,X
			LDR P,=0
			LDR Q,=0
			
			LDR I,=1
			
WHILE
			CMP I,K
			BHI FINISH
			
			CMP R,#0
			BEQ FINISH
		
IF
			CMP R,#0
			BLE IF_ELSE
			
			LSL TMP,R,#1   ; 2 * R
			
			SUB TMP1,P,Q   ; P - Q
			LSL TMP1,#1    ; 2 * (P - Q)
			
			SUB TMP,TMP1   ; 2 * R - 2 * (P - Q)
			
			SUB INDEX,K,I
		
			LSL TMP1,ONE,INDEX ; 2^-i
			
			SUB TMP,TMP1   ; 2 * R - 2 * (P - Q) - 2^-i
			
			MOV R,TMP
			
			ADD P,P,TMP1
			
			
			B NEXT
IF_ELSE
			
			LSL TMP,R,#1   ; 2 * R
			
			SUB TMP1,P,Q   ; P - Q
			LSL TMP1,#1    ; 2 * (P - Q)
			
			ADD TMP,TMP1   ; 2 * R + 2 * (P - Q)
			
			SUB INDEX,K,I
		
			LSL TMP1,ONE,INDEX ; 2^-i
			
			SUB TMP,TMP1   ; 2 * R - 2 * (P - Q) - 2^-i
			
			ADD Q,Q,TMP1
			
			B NEXT

NEXT
			ADD I,#1
			B WHILE
FINISH
			
			SUB TMP,P,Q
			MOV R0, TMP
					
			   
	        POP{R4-R8,R10-R11,PC}
			ENDP
			END
				
					
	