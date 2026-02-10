X			RN 0
K			RN 1
R			RN 2
Q			RN 3
T			RN 4
I			RN 5
TMP			RN 6
ONE	     	RN 7
TMP1		RN 8
INDEX       RN 9

			AREA MY_CODE,CODE, READONLY
				
restoringSquareRoot	PROC
			EXPORT restoringSquareRoot
			PUSH{R4-R8,R10-R11,LR}
			
			LDR I,=1
			
			LSL R,X,#1     ; R = 2X
			
			LDR Q,=0      ; Q = 0
			
			LDR ONE,=1
			
			SUB INDEX,K,I
			LSL T,ONE,INDEX  ; T = 2 ^ -1     0100000
			
FOR
			
			CMP R,T             ; R >= T
			BHS IF_COND
			
			B COMPUTATION    
IF_COND
			SUB R,R,T            ; R = R-T
			
			SUB INDEX,K,I
			LSL TMP,ONE,INDEX         ; 2 ^ -i
			
			ADD Q,Q,TMP         ; Q = Q + 2^-i
			
COMPUTATION			
			LSL TMP,Q,#1  ;2*Q 
			
			ADD INDEX,I,#1
			SUB INDEX,K,INDEX     
			LSL TMP1,ONE,INDEX  ; 2 ^ -(i+1)
			
			ADD T,TMP,TMP1      ; T = 2*Q + 2^-(i+1)
			
			LSL R,R,#1          ; r = 2*r
			
			
			
			CMP K,I
			BEQ FINISH
			
			ADD I,#1
			
			B FOR
			
FINISH
			
			MOV R0, Q
					
			   
	        POP{R4-R8,R10-R11,PC}
			ENDP
			END
				
					
	