X			RN 0
N			RN 1
Y			RN 2
M			RN 3
N_P			RN 4
M_P			RN 5
CNT			RN 6
TMP			RN 7
P		    RN 8
Q			RN 10
R			RN 11

			AREA MY_CODE,CODE, READONLY
				
computeG	PROC
			EXPORT computeG
			PUSH{R4-R8,R10-R11,LR}
			
			; STEP 0 CALCULATE N` AND  M`
			LDR CNT,=0
FOR_X		
			CMP CNT,#31
			BEQ NEXT_X
			
			LSR TMP,X,CNT
			AND TMP,#1
			
			CMP TMP,#1
			IT NE
		    ADDNE CNT,#1
			BEQ NEXT_X
			
			B FOR_X
NEXT_X
	        SUB N_P,N,CNT
            LSR X,CNT
			
			LDR CNT,=0
FOR_Y			
			CMP CNT,#31
			BEQ NEXT_Y
			
			LSR TMP,Y,CNT
			AND TMP,#1
			
			CMP TMP,#1
			IT NE
		    ADDNE CNT,#1
			BEQ NEXT_Y
			
			B FOR_Y
NEXT_Y
	        SUB M_P,M,CNT
            LSR Y,CNT

			;STEP 1
		    MUL TMP,X,X         ; X^2
			ADD P,N_P,N_P       ; P = N` + N`
			
			;STEP 2 
			MUL TMP,Y,TMP     ; Y * X^2
			ADD Q,P,M_P       ; Q = P + M`
			
			;STEP 3
			LDR CNT,=3
			LSL CNT,Q
			SUB TMP,CNT,TMP   ; 3 – y * x^2
			
			;STEP 4
			MUL TMP,X,TMP     ; X * (3 – y * x^2)
			ADD R,Q,N_P       ; r = q + n'
			
            ;STEP 5
			LSR TMP,TMP,#1       ; (X * (3 – y * x^2)) / 2
			
			;STEP 6
			CMP N,M
			ITE HI
			MOVHI CNT,N
			MOVLS CNT,M
			
			SUB CNT,R,CNT
			CMP CNT,#0
			BLT CHECK
			
			B FINISH
			
			
CHECK 
			LDR Q,=-1
			MUL CNT, CNT,Q
			
FINISH			
			
			LSR TMP,CNT 
			
			
			MOV R0,TMP
			
			
	        POP{R4-R8,R10-R11,PC}
			ENDP
			END
				
					
	