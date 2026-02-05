AREA_		RN 0
N			RN 1
CNT			RN 2
INDEX		RN 3
TMP			RN 4
X		    RN 5
CNT1		RN 6
FOUND		RN 7


			AREA MY_CODE,CODE, READONLY
				
Recaman	PROC
			EXPORT Recaman
			PUSH{R4-R8,R10-R11,LR}
			LDR CNT,=0
FOR
			CMP CNT,N
			BEQ FINISH
			
			CMP CNT,#0
			ITT  EQ
			STREQ CNT,[AREA_,CNT]
			ADDEQ  CNT,#1
			
			
			
SECOND_COND
			SUB INDEX,CNT,#1
			LDRB TMP,[AREA_,INDEX]   ; R(N-1)
			SUB X,TMP,CNT             ; R(N-1) - N
			
			CMP X,#0
			BGT CHECK_EXIST
			B THIRD_COND
			
CHECK_EXIST
			LDR CNT1,=0
			LDR FOUND,=0
FOR1
			CMP CNT1,CNT
			BEQ STORE_VAL
			
			LDRB TMP,[AREA_,CNT1]
			
			CMP TMP,X
			ITT EQ
			LDREQ	FOUND,=1
			BEQ THIRD_COND
			
			
			ADD CNT1,#1
			B FOR1
			
			
STORE_VAL
			STR X,[AREA_,CNT]            
			ADD CNT,#1
			B FOR
THIRD_COND
			SUB INDEX,CNT,#1
			LDRB TMP,[AREA_,INDEX]   ; R(N-1)
			ADD X,TMP,CNT             ; R(N-1) + N
		    STR X,[AREA_,CNT]
			
			ADD CNT,#1
			B FOR
			
			
FINISH
			
			   
	        POP{R4-R8,R10-R11,PC}
			ENDP
			END
				
					
	