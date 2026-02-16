U				RN 0
L				RN 1
D				RN 2
FLAG			RN 3
TMP				RN 4
TMP1			RN 5
NEG_			RN 6



				AREA MY_CODE,CODE,READONLY
SDIV64S			PROC
	            EXPORT SDIV64S
				PUSH{R4-R8,R10-R11,LR}
				LDR NEG_,=-1
				
;				CMP U,#0
;				ITE	LE
;				LDRLE TMP,=-1
;				LDRGT TMP,=1
;				
;				CMP D,#0
;				ITE	LE
;				LDRLE TMP1,=-1
;				LDRGT TMP1,=1
				
				AND TMP,U,#2_1000     ; GET FIRST BIT OF THE U
				AND TMP1,D,#2_1000    ; GET FIRST BIT OF THE D
				
				CMP TMP,TMP1
				ITE EQ 
				LDREQ FLAG,=1
				LDRNE FLAG,=0
				
				CMP TMP,#-1
				IT EQ
				MULEQ U,NEG_
				
				CMP TMP1,#-1
				IT EQ
				MULEQ D,NEG_
				
				
				
				
				POP{R4-R8,R10-R11,PC}
				ENDP
				END
					