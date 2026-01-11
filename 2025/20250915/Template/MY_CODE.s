N				RN 0
CNT				RN 1
TMP				RN 2
TMP1			RN 3
RESULT          RN 4


				AREA MY_CODE, CODE, READONLY
					
aliquotSum 		PROC
				EXPORT aliquotSum
				PUSH{R4-R8,R10-R11,LR}
				LDR CNT,=1
				LDR RESULT,=0
FOR
				CMP CNT,N
				BEQ FINISH
				
				UDIV TMP,N,CNT
				MUL  TMP,CNT
				SUB TMP,N,TMP
				
				CMP TMP,#0
				BEQ NEXT
				
				ADD CNT,#1
				B FOR
NEXT
				ADD RESULT,RESULT,CNT
				ADD CNT,#1
				B FOR
				
FINISH 
				CMP RESULT,N
				BEQ perfect 
				BHI	abundant 
				BLO deficient 
perfect 
				MOV R0,1
				B EXIT
abundant 
				MOV R0,2
				B EXIT
deficient 
				MOV R0,0
				B EXIT
EXIT			
				POP{R4-R8,R10-R11,PC}
				ENDP
				END
					