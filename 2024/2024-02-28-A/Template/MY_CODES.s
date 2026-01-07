ROW				RN 0
COL				RN 1
MAZE			RN 2
ALL				RN 3
CNT		        RN 4
CURRENT         RN 5
TMP				RN 6         
TMP1            RN 7
VALUE			RN 8

				
				AREA MY_CODE, CODE, READONLY
				

shortestPath1  	PROC
				EXPORT  shortestPath1
				PUSH{R4-R8,R10-R11,LR}
				
				MUL ALL, ROW, COL
				
				LDR VALUE,=0


WHILE           
				LDR CNT,=0
				
				CMP VALUE,#'e'
				BEQ FINISH 

				CMP VALUE,#0
				BEQ CHECK_EQUAL
				ADD VALUE,#1
				B FOR 
				
CHECK_EQUAL     
                MOV VALUE,CURRENT 
				ADD VALUE,#'0'
				ADD VALUE,#1
				B FOR		
FOR				
				CMP ALL,#0
				BEQ WHILE
				
				LDRB CURRENT,[MAZE,CNT]
				
				SUB TMP,VALUE,#1
                CMP CURRENT,TMP
				BEQ TOP 
				
				ADD CNT,#1
				B FOR 
TOP				
                SUB TMP,CNT,COL ;TOP
				LDRB TMP1,[MAZE,TMP]
				
				CMP TMP1,#'X'
				BEQ RIGHT
				
				CMP TMP1,#' '
				BNE RIGHT
			
                STRB VALUE,[MAZE,TMP]
				
RIGHT
                ADD TMP,CNT,#1 ;RIGHT
				LDRB TMP1,[MAZE,TMP]
				
				CMP TMP1,#'X'
				BEQ BOTTOM
				
				CMP TMP1,#' '
				BNE BOTTOM
				
                STRB VALUE,[MAZE,TMP]
				
BOTTOM	
				ADD TMP,CNT,COL ;BOTTOM
				LDRB TMP1,[MAZE,TMP]
				
				CMP TMP1,#'X'
				BEQ LEFT
				
				CMP TMP1,#' '
				BNE LEFT
				
                STRB VALUE,[MAZE,TMP]
LEFT 			
				ADD CNT,#1
				SUB TMP,CNT,#1 ;LEFT
				LDRB TMP1,[MAZE,TMP]
				
				CMP TMP1,#'X'
				BEQ FOR
		
		        CMP TMP1,#' '
				BNE FOR
				
                STRB VALUE,[MAZE,TMP]

				
				
FINISH 
                 
				POP{R4-R8,R10-R11,LR}
				ENDP
				END