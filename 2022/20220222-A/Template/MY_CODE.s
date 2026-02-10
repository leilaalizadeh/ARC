X			RN 0
N			RN 1
Y			RN 2
M			RN 3
A			RN 4
B_			RN 5
C			RN 6
D			RN 7
TMP			RN 8
TMP1        RN 10
ONE			RN 11
			
			AREA MY_CODE,CODE, READONLY
				
computeF	PROC
			EXPORT computeF
			PUSH{R4-R8,R10-R11,LR}
			
			LDR ONE,=1
			MOV	A,M
			MOV B_,N
			LDR C,=31
			
			;STEP 0: FINDING C VALUE 
LOOP_C
			CMP C,#0
			BEQ SHIFT_Y
			
			LSR TMP,Y,C
			AND TMP,ONE
			
			CMP TMP,#1
			BEQ SHIFT_Y
			
			SUB C,#1
			
			B LOOP_C
			
SHIFT_Y
			LDR TMP,=31
			SUB C,TMP,C    ;26
			
			;STEP 1   SHIFT Y AND CALCULATE D VALUE 
			LSL Y,C
			UDIV TMP,Y,X    ; Q = Y/X LSR TMP,X,Y
			ADD D,A,C       ; M + C
			SUB D,B_        ; D = M + C - B
			
			;STEP 2
			CMP N,D         ; N FRACTIONAL DIGIT OF X , D FRACTIONAL DIGIT OF Q 
			BLT ADDITION    ; SAME SCALE IN ORDER TO ADD 2 NUMBER 
			
			B STEP3
			
ADDITION    ; N < D
			SUB TMP1,D,N    ; D - N  27 - 2 = 25
			LSL X,X,TMP1    ; X << 25  TO MAKE SAME SCALE 
			
		    ADD TMP,X,TMP   ; S = X + Q
			
			
			B STEP3
			
STEP3
			LDR TMP1,=1
			LSR TMP,TMP,TMP1   ; FSCALED = S / 2
			
			
			CMP N,M
			ITE HI
			MOVHI TMP1,N        ; K = N
			MOVLS TMP1,M        ; K = M
			
			SUB A,D,TMP1    ; D - K    27 - 3 = 24
			
			LSR ONE,TMP,A   ; FSCALED >> 24   FSCLAED / 2^24
			
            MOV R0,ONE
			
	        POP{R4-R8,R10-R11,PC}
			ENDP
			END
				
					
	