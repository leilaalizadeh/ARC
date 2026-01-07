;        AREA    MY_CODE, CODE, READONLY
;        EXPORT  depthFirstSearch
;        EXPORT  chooseNeighbor

;; -------------------------
;; Parameter aliases (AAPCS)
;; depthFirstSearch(MAZE, NROW, NCOL, START)
;; -------------------------
;MAZE    RN 0        ; r0 = base address of maze (byte array)
;NROW    RN 1        ; r1 = NUM_ROW (not needed for DFS logic here)
;NCOL    RN 2        ; r2 = NUM_COL
;START   RN 3        ; r3 = start index

;; -------------------------
;; Working register aliases
;; -------------------------
;BASE    RN 4        ; saved maze base (so r0 can be reused)
;COLS    RN 5        ; saved NUM_COL
;CUR     RN 6        ; current index
;IDX     RN 7        ; temp index
;CURADR  RN 8        ; &maze[CUR]
;CURVAL  RN 9        ; byte value at current cell
;SPBASE  RN 10       ; stack base marker (to detect empty DFS stack)
;NBRADR  RN 11       ; &maze[neighbor]

;; ============================================================
;; depthFirstSearch
;; ============================================================
;depthFirstSearc PROC
;        PUSH    {r4-r11, lr}

;        MOV     BASE, MAZE        ; keep maze base safe
;        MOV     COLS, NCOL        ; keep num_col safe
;        MOV     CUR,  START       ; current = start index

;        MOV     SPBASE, sp        ; stack base after prologue (empty DFS stack marker)

;        ; mark start visited: maze[start] |= 1
;        ADD     CURADR, BASE, CUR
;        LDRB    CURVAL, [CURADR]
;        ORR     CURVAL, CURVAL, #1
;        STRB    CURVAL, [CURADR]

;DFS_loop
;        ; Build neighbor visited flags in r0..r3:
;        ; r0 = bit0 of right neighbor (0 unvisited, 1 visited)
;        ; r1 = bit0 of bottom neighbor
;        ; r2 = bit0 of left neighbor
;        ; r3 = bit0 of top neighbor

;        ; right: CUR+1
;        ADD     IDX, CUR, #1
;        LDRB    r0, [BASE, IDX]
;        AND     r0, r0, #1

;        ; bottom: CUR+COLS
;        ADD     IDX, CUR, COLS
;        LDRB    r1, [BASE, IDX]
;        AND     r1, r1, #1

;        ; left: CUR-1
;        SUB     IDX, CUR, #1
;        LDRB    r2, [BASE, IDX]
;        AND     r2, r2, #1

;        ; top: CUR-COLS
;        SUB     IDX, CUR, COLS
;        LDRB    r3, [BASE, IDX]
;        AND     r3, r3, #1

;        BL      chooseNeighbo    ; returns 0..4 in r0

;        CMP     r0, #0
;        BEQ     NoNeighbor

;        ; push current index for backtracking
;        PUSH    {CUR}

;        ; load current cell byte
;        ADD     CURADR, BASE, CUR
;        LDRB    CURVAL, [CURADR]

;        ; r0: 1=R, 2=D, 3=L, 4=U
;        CMP     r0, #1
;        BEQ     MoveRight
;        CMP     r0, #2
;        BEQ     MoveDown
;        CMP     r0, #3
;        BEQ     MoveLeft
;        ; else -> MoveUp

;MoveUp
;        SUB     IDX, CUR, COLS            ; neighbor index
;        ADD     NBRADR, BASE, IDX
;        LDRB    r1, [NBRADR]              ; neighbor byte
;        ORR     CURVAL, CURVAL, #0x10     ; current: TOP (bit4)
;        ORR     r1,     r1,     #0x04     ; neighbor: BOTTOM (bit2)
;        B       FinishMove

;MoveRight
;        ADD     IDX, CUR, #1
;        ADD     NBRADR, BASE, IDX
;        LDRB    r1, [NBRADR]
;        ORR     CURVAL, CURVAL, #0x02     ; current: RIGHT (bit1)
;        ORR     r1,     r1,     #0x08     ; neighbor: LEFT  (bit3)
;        B       FinishMove

;MoveDown
;        ADD     IDX, CUR, COLS
;        ADD     NBRADR, BASE, IDX
;        LDRB    r1, [NBRADR]
;        ORR     CURVAL, CURVAL, #0x04     ; current: BOTTOM (bit2)
;        ORR     r1,     r1,     #0x10     ; neighbor: TOP    (bit4)
;        B       FinishMove

;MoveLeft
;        SUB     IDX, CUR, #1
;        ADD     NBRADR, BASE, IDX
;        LDRB    r1, [NBRADR]
;        ORR     CURVAL, CURVAL, #0x08     ; current: LEFT  (bit3)
;        ORR     r1,     r1,     #0x02     ; neighbor: RIGHT (bit1)
;        ; fallthrough

;FinishMove
;        ORR     r1, r1, #1                ; neighbor visited (bit0)
;        STRB    CURVAL, [CURADR]          ; store current updated
;        STRB    r1,     [NBRADR]          ; store neighbor updated

;        MOV     CUR, IDX                  ; current = neighbor
;        B       DFS_loop

;NoNeighbor
;        ; If DFS stack empty => done
;        CMP     sp, SPBASE
;        BEQ     DFS_done

;        ; else pop and continue
;        POP     {CUR}
;        B       DFS_loop

;DFS_done
;        POP     {r4-r11, pc}
;        ENDP


;; ============================================================
;; chooseNeighbor
;; Inputs:
;;   r0 rightVisited (0 unvisited / 1 visited)
;;   r1 bottomVisited
;;   r2 leftVisited
;;   r3 topVisited
;; Output:
;;   r0 = 1..4 or 0 (priority: right, bottom, left, top)
;; ============================================================
;chooseNeighbo PROC
;        CMP     r0, #0
;        MOVEQ   r0, #1
;        BXEQ    lr

;        CMP     r1, #0
;        MOVEQ   r0, #2
;        BXEQ    lr

;        CMP     r2, #0
;        MOVEQ   r0, #3
;        BXEQ    lr

;        CMP     r3, #0
;        MOVEQ   r0, #4
;        BXEQ    lr

;        MOV     r0, #0
;        BX      lr
;        ENDP

;        END
