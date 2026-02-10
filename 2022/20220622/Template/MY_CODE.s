X			RN 0
K			RN 1
R			RN 2
Q			RN 3
CNT 		RN 4
TMP			RN 5
TMP1		RN 6
ONE         RN 7
TMP2		RN 8

			AREA MY_CODE,CODE, READONLY
				
squareRoot	PROC
			EXPORT squareRoot
			PUSH{R4-R8,R10-R11,LR}
			LDR R,=2_0100110
			LDR Q,=2_0000000
			
			LDR CNT,=1
LOOP
			LSL R,R,#1     ; R = 2 * R
			
			SUB TMP1,K,CNT   ; K-1, K-2, K-3, K-4, K-5, K-6
			LDR ONE,=1
			LSL ONE,TMP1
			
			ADD TMP,Q,ONE    ; Q + 2 ^-i
			
			CMP R,TMP        ;r  >= Q + 2 ^-i:
			BGE CHECK_IF
			BLT CHECK_ELSE
			
			B NEXT
CHECK_IF 
			LSL TMP2,Q,#1      ; 2 * Q
			SUB R,R,TMP2       ; R = R - 2 * Q
			SUB R,ONE          ; R = R - 2 ^ -i
			MOV Q,TMP          ; Q = Q + 2 ^-i
			
			B NEXT
			
CHECK_ELSE
			LDR TMP2,=-1
			MUL TMP,TMP2
			
			CMP R,TMP         ; r < -(Q + 2^-i):
			BGE NEXT
			
			LSL TMP2,Q,#1      ; 2 * Q
			ADD R,R,TMP2       ; R = R + 2 * Q
			SUB R,ONE          ; R = R - 2 ^ -i
			SUB Q,Q,ONE        ; Q = Q - 2 ^-i

			
NEXT
			
			CMP CNT,K
			BEQ FINISH
			
			ADD CNT,#1
			
			B LOOP
			
FINISH
			MOV R0,Q
			
	        POP{R4-R8,R10-R11,PC}
			ENDP
			END
				
					
	