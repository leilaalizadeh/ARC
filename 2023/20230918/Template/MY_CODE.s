A          RN 0
Q          RN 7
REM        RN 8
TMP        RN 9
SUM        RN 10
TEN        RN 11

           AREA MY_CODE,CODE,READONLY

digitSum   PROC
           EXPORT digitSum
           PUSH {R7-R11,LR}

           LDR TEN,=10
           MOV SUM,#0           ; sum = 0

LOOP
           UDIV Q,A,TEN         ; Q = A / 10
           MUL  TMP,Q,TEN       ; TMP = Q * 10
           SUB  REM,A,TMP       ; REM = A - TMP  
           ADD  SUM,SUM,REM     ; SUM = SUM + REM
           MOV  A,Q             ; NEW VALUE
           CMP  A,#0
           BNE  LOOP         

           ADD  R0,R0,SUM      ; RETURN SUM

           POP {R7-R11,PC}
           ENDP




SERIES     RN 0
N          RN 1
CURR       RN 2
SUM_DIGITS RN 3
BASS_ADDR  RN 4
DIGIT	   RN 5
CNT		   RN 6

digitaddition PROC
           EXPORT digitaddition
           PUSH{R4-R6,LR} 

           MOV  BASS_ADDR,SERIES       ; save base address into R4
           MOV  SUM_DIGITS,#0          ; grand digit-sum = 0
           MOV CNT,#1
		   
           ;  N <= 0
           CMP  N,#0
           BLE  DA_RETZERO

           LDRB  CURR,[BASS_ADDR]     ; 47

           ; CALL SUBROUTINE
           MOV  R0,CURR              ; R0 = 47
           BL   digitSum             ; 11
		   
		   ; R0 RETURN VALUE OF digitSum 
		   MOV  DIGIT,R0
           ADD  SUM_DIGITS,R0            ; SUM DIGITS
		   
           ADD  CURR,CURR,DIGIT    ; 47 + 11 = 58
           STRB CURR, [BASS_ADDR,CNT] 
		   ADD  CNT,#1
		   
           SUBS N,N,#1          
		   
		   CMP  N,#1
           BEQ  DA_DONE         ; if N was 1, finished

DA_LOOP
           MOV  R0,CURR
           BL   digitSum    
           MOV  DIGIT,R0		   
           ADD  SUM_DIGITS,R0      ;
           ADDS CURR,CURR,DIGIT    ; 58 + 14 = 59 does CURR + DIGIT and SETS FLAGS
		   BCS  DA_RETZERO        ; if Carry=1 ? result exceeded 0xFFFFFFFF ? overflow
		   STRB CURR, [BASS_ADDR,CNT] 
		   ADD  CNT,#1

           SUBS N,N,#1  
		   CMP  N,#1		   
           BNE  DA_LOOP
DA_DONE
		   MOV  R0,CURR
           BL   digitSum    
           MOV  DIGIT,R0		   
           ADD  SUM_DIGITS,R0
		   
           MOV  R0,SUM_DIGITS       
           POP  {R4-R6,PC}

DA_RETZERO
           MOV  R0,#0           ; return 0 on overflow or N<=0
           POP  {R4-R6,PC}

           ENDP
           END