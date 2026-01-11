ROW				RN 0
COL				RN 1
MAZE			RN 2
ALL				RN 3
CNT		        RN 4
CURRENT         RN 5
TMP				RN 6         
TMP1            RN 7
VALUE			RN 8
FLAG            RN 10

				
				AREA MY_CODE, CODE, READONLY
				

shortestPath  	PROC
				EXPORT  shortestPath
				PUSH{R4-R8,R10-R11,LR}
				
				MUL ALL,ROW,COL
				LDR VALUE,=0
				LDR FLAG,=0
WHILE
                CMP FLAG,#1
				BEQ FINISH

                CMP VALUE,#9
				BEQ EXIT

				LDR CNT,=0
				
FOR             
				CMP ALL,CNT
				BEQ FINISH
				
				LDRB CURRENT,[MAZE,CNT]
				
				CMP   CURRENT, #'X'
				BNE   IF_CHECK
				ADD   CNT, CNT, #1       
				B   FOR             

				
IF_CHECK
                CMP VALUE,#0
				IT NE
				SUBNE CURRENT,#"0"
				
				CMP CURRENT,VALUE
                BEQ TOP		
				ADD   CNT, CNT, #1
				B FOR
				
TOP				
				SUB TMP,CNT,COL ; TOP
				LDRB TMP1,[MAZE,TMP]
				CMP TMP1,#'e'
				BEQ EXIT
				
				CMP TMP1,#' '
				BNE LEFT
				
                ADD TMP1,VALUE,#1
				ADD TMP1,#'0'
				STRB TMP1,[MAZE,TMP]
				
LEFT				
				SUB TMP,CNT,#1
				LDRB TMP1,[MAZE,TMP]
				CMP TMP1,#'e'
				BEQ EXIT
				CMP TMP1,#' '
				BNE RIGHT  
 	            
				ADD TMP1,VALUE,#1
				ADD TMP1,#'0'
				STRB TMP1,[MAZE,TMP]
				
RIGHT
				ADD TMP,CNT,#1
				LDRB TMP1,[MAZE,TMP]
				CMP TMP1,#'e'
				BEQ EXIT 
				CMP TMP1,#' '
				BNE BOTTOM 
				
				ADD TMP1,VALUE,#1
				ADD TMP1,#'0'
				STRB TMP1,[MAZE,TMP]
				
BOTTOM				
				ADD TMP,CNT,COL
				ADD CNT,#1
				LDRB TMP1,[MAZE,TMP]
				CMP TMP1,#'e'
				BEQ EXIT
				CMP TMP1,#' '
				BNE FOR 
				
				ADD TMP1,VALUE,#1
				ADD TMP1,#'0'
				STRB TMP1,[MAZE,TMP]
				
				
				
				CMP ALL,CNT
				BEQ FINISH
				
				B FOR
				
FINISH				
				ADD VALUE,#1
				LDR	  FLAG,=0
				B WHILE

EXIT
				MOV R0,VALUE
				
			    POP{R4-R8,R10-R11,PC}
				ENDP
				END