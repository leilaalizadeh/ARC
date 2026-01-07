ROW 					RN 0
COL						RN 1
MAZE					RN 2
CNT						RN 3
CURRENT					RN 4
INDEX					RN 5
TMP						RN 6
CNT1					RN 7
ALL						RN 8
FLAG					RN 9
CNTWHILE				RN 10

						AREA MY_CODE, CODE, READONLY
deadEndFilling			PROC
					    EXPORT deadEndFilling
						PUSH{R4-R8,R10-R11,LR}
						
						
						MUL ALL, ROW,COL
						LDR FLAG,=0
						LDR CNTWHILE,=0
						
WHILE 	
						LDR CNT,=0
						
						LDR FLAG,=0 
						
FOR 
						CMP ALL, CNT
						BEQ FINISH
						
						LDR CNT1,=0
						
						LDRB CURRENT,[MAZE,CNT]
						CMP CURRENT,#' '
						BEQ TOP
						ADD CNT,#1
						B FOR
						
TOP
						SUB INDEX,CNT,COL
						LDRB CURRENT,[MAZE,INDEX] ;TOP VALUE
						
						CMP CURRENT,#'*'
						IT EQ
						ADDEQ CNT1,#1
						
						B RIGHT 

RIGHT 
						ADD INDEX,CNT,#1
						LDRB CURRENT,[MAZE,INDEX] ;RIGHT VALUE
						
						CMP CURRENT,#'*'
						IT EQ
						ADDEQ CNT1,#1
						
						B LEFT 

LEFT
						SUB INDEX,CNT,#1
						LDRB CURRENT,[MAZE,INDEX] ;LEFT VALUE
						
						CMP CURRENT,#'*'
						IT EQ
						ADDEQ CNT1,#1
						
						B BOTTOM 
BOTTOM
						ADD INDEX,CNT,COL
						LDRB CURRENT,[MAZE,INDEX] ;BOTTOM VALUE
						
						CMP CURRENT,#'*'
						IT EQ
						ADDEQ CNT1,#1
						
						B NEXT
NEXT			
						LDR TMP,='*'
						CMP CNT1,#3
						IT  HS
						STRBHS TMP,[MAZE,CNT]
						ADDHS FLAG,#1
						
						
						ADD CNT,#1
						B FOR 
						
FINISH						
                        CMP FLAG,#0
						BEQ RESULT
						
						ADD CNTWHILE,#1
						B WHILE 
						
RESULT						
						
						POP{R4-R8,R10-R11,PC}
						ENDP
						END
	