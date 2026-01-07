MAZE				RN 0
NUM_ROW				RN 1
NUM_COL				RN 2
START_MATRIX	    RN 3

; BECAUSE WE WILL USE R0-R3 FOR THE SECOND SUBROUTINES WE SHOULD MOVE THE R0-R3 TO NEW REGISTERS TO PREVENT OVERWRINTING 


MAZE_C              RN 4
COL_C			    RN 5
START_C  			RN 6
CURRENT_VAL			RN 7
CURRENT_ADD			RN 8
SPBASE				RN 9
NB_VAL				RN 10
INDEX				RN 11


					AREA MY_CODE,CODE,READONLY
					
depthFirstSearch	PROC
					PUSH{R4-R8,R10-R11,LR}
					EXPORT depthFirstSearch
					
					;; MOVE TO NEW REGISTERS 
					MOV MAZE_C,MAZE
					MOV COL_C,NUM_COL
					MOV START_C,START_MATRIX
					
					MOV     SPBASE, sp        ; stack base after prologue (empty DFS stack marker)
					
					;;START
					
					ADD CURRENT_ADD,MAZE_C,START_C
					LDRB CURRENT_VAL, [CURRENT_ADD]
					ORR CURRENT_VAL, CURRENT_VAL,#1
					STRB CURRENT_VAL,[CURRENT_ADD]
					
					
LOOP  
					; Build neighbor visited flags in r0..r3:
					; r0 = bit0 of right neighbor (0 unvisited, 1 visited)
					; r1 = bit0 of bottom neighbor
					; r2 = bit0 of left neighbor
					; r3 = bit0 of top neighbor
						
						
					; right: START+1
					ADD INDEX,START_C,#1      ;8
					LDRB R0,[MAZE_C,INDEX]    ; R0 = MAZE[8]
					AND R0,R0,#1  ;RIGHT VALUE  ; BIT 0 RO BEDE BAGIYARO 0 KON - X AND 1 = X 
					
					; bottom: START + NUM_COL
					ADD INDEX,START_C,COL_C   ;7+5
					LDRB R1,[MAZE_C,INDEX]
					AND R1,R1,#1    
					
					; left: START - 1
					SUB INDEX,START_C,#1      ;7-1
					LDRB R2,[MAZE_C,INDEX]
					AND R2,R2,#1
					
					; top: START - NUM_COL
					SUB INDEX,START_C,COL_C   ;7-5
					LDRB R3,[MAZE_C,INDEX]
					AND R3,R3,#1
					
					BL      chooseNeighbor    ; returns 0..4 in r0

					CMP     R0, #0 ;WHICH PLACE?
					BEQ     NoNeighbor

					; push current index for backtracking
					PUSH {START_C}
					
					ADD  CURRENT_ADD, MAZE_C, START_C
                    LDRB CURRENT_VAL,[CURRENT_ADD]
					
					; r0: 1=RIGHT, 2=BOTTOM, 3=LEFT, 4=UP
					CMP     R0, #1
					BEQ     MoveRight
					CMP     R0, #2
					BEQ     MoveDown
					CMP     R0, #3
					BEQ     MoveLeft
					 ; else -> MoveUp
					 
MoveUp
					SUB INDEX,START_C,COL_C
					LDRB NB_VAL,[MAZE_C,INDEX]
					ORR CURRENT_VAL,CURRENT_VAL, #0x10 ;BIT 4 - 1 << 4 ->0001 0000  0x10 2^4 = 16  - x OR 1 = 1
					ORR NB_VAL,NB_VAL,#0x04          ;BIT 2 -> 1 << 2 -> 0000 0100  0X04 2^2 = 4 -  BOTTOM HAM BAZE - YEKTARFE NASHE 
					B FinishMove
MoveRight
					ADD INDEX,START_C,#1
					LDRB NB_VAL,[MAZE_C,INDEX]
					ORR CURRENT_VAL,CURRENT_VAL,#0x02  ;BIT 1 - 1 << 1 -> 0000 0010 0x02 2^1 = 2
					ORR NB_VAL,NB_VAL,#0x08            ;BIT 3 - 1 << 3 -> 0000 1000 0x08 2^3 = 8
					B FinishMove
MoveDown
                    ADD INDEX,START_C,COL_C
			
					LDRB NB_VAL,[MAZE_C,INDEX]
					ORR CURRENT_VAL,CURRENT_VAL,#0x04   ;BIT 2 - 1 << 2 -> 0000 0100 0x04 2^2 = 4
					ORR NB_VAL,NB_VAL,#0x10             ;BIT 4 - 1 << 4 -> 0001 0000 0X10 2^4 = 16
					B FinishMove
MoveLeft
					SUB INDEX,START_C,#1
					
					LDRB NB_VAL,[MAZE_C,INDEX]
					ORR CURRENT_VAL,CURRENT_VAL,#0x08   ;BIT 3 - 1 << 3 -> 0000 1000 0x08 2^3 = 8
					ORR NB_VAL,NB_VAL,#0x02             ;BIT 1 - 1 << 1 -> 0000 0010 0x02 2^1 = 2
					B FinishMove
					
FinishMove
					ORR NB_VAL,NB_VAL,#1    ; X OR 1 = 1
					STRB CURRENT_VAL,[CURRENT_ADD]
					STRB NB_VAL, [MAZE_C,INDEX]
					
					MOV START_C,INDEX
					B LOOP
					
NoNeighbor 
					; If DFS stack empty => done
					CMP	sp, SPBASE
					BEQ Finish
					; else pop and continue
					POP {START_C}
					B LOOP				
Finish					
					
					POP{R4-R8,R10-R11,PC}
					ENDP
						
chooseNeighbor		PROC
					
					CMP     R0, #0
					MOVEQ   R0, #1   ; AGE RIGHT KHALI BASHAD MEGDAR R0=1 VA BORO BE RISHT 
					BXEQ    LR       ; branch + exchange - HAMINJA TAMUM KON BORO BE SAMTE RAST 
					
					CMP     R1, #0
					MOVEQ   R0, #2
					BXEQ    LR
					
					CMP     R2, #0
					MOVEQ   R0, #3
					BXEQ    LR
					
					CMP     R3, #0
					MOVEQ   R0, #4
					BXEQ    LR
					
					MOV     R0, #0   ; HICH HAMSAYE KHALI NADARD 
					BX      LR
		
					ENDP

chooseRandomNeighbor	PROC
						PUSH{R4-R8,R10-R11,LR}
						CMP     R0, #1
						CMP     R1, #2
						CMP     R2, #3
						CMP     R3, #4
						
						POP{R4-R8,R10-R11,PC}
						ENDP


					END