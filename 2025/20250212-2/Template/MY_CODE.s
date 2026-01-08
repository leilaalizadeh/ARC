Y				RN 0
N				RN 1
CNT				RN 2
TMP				RN 3
TMP1			RN 4
VAL				RN 5
VAL1			RN 6
RESULT			RN 7

				AREA MY_CODE, CODE, READONLY

Maclaurin		PROC
				EXPORT Maclaurin
				PUSH{R4-R8,R10-R11,LR}
				
				LDR VAL,=100
				LDR CNT,=1
				MOV RESULT ,VAL
FOR 
				CMP CNT,N
				BHI FINISH
				
				MUL TMP,Y,Y
				
;				NEG VAL,VAL
				LDR TMP1,=0
				SUB TMP1,#1
				MUL VAL,TMP1
				
				MUL TMP,VAL
				
				
				
				LDR VAL1,=2
				MUL VAL1,CNT       ;2i
				
				SUB TMP1, VAL1,#1  ;2i - 1
				
				MUL TMP1,VAL1,TMP1 ;(2i) * (2i - 1)
				LDR VAL1,=100
				MUL VAL1,TMP1
				
				SDIV VAL,TMP,VAL1
				
				ADD RESULT,VAL
				
				ADD CNT,#1
				B FOR 				
				
FINISH
				
				MOV R0, RESULT	
				
				POP{R4-R8,R10-R11,PC}
				ENDP
			    END
					