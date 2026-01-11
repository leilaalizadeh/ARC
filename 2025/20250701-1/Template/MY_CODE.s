SEED		RN 0
A			RN 1
C			RN 2
N			RN 3
M 			RN 4
TMP			RN 5
TMP1		RN 6
TMP2		RN 7
			AREA MY_CODE,CODE, READONLY


nextElementLCG PROC
	           EXPORT nextElementLCG
			   PUSH{R4-R8,R10-R11,LR}
			   LDR M,[SP,#32]
			   MUL TMP,SEED,A     ; SEED * A
			   ADD TMP,C          ; (SEED * A) + C
			   
			   EOR TMP,N          ; ((SEED * A) + C ) XOR N
			   
			   UDIV TMP1,TMP,M    ; (((SEED * A) + C ) XOR N) / M = Q
			   
			   MUL TMP2,M,TMP1    ;  M * Q
			   SUB TMP,TMP2       ;  (((SEED * A) + C ) XOR N) - (M * Q)
			   
			   
			   MOV R0,TMP
			   
	           POP{R4-R8,R10-R11,PC}
			   ENDP
				   
			END