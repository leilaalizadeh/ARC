        AREA MY_CODE, CODE, READONLY
        

; ---------------- Register names (RN) ----------------
ROW         RN 0        ; input rows, later loop var, finally return value
COL         RN 1        ; input cols, later loop var
MAZE        RN 2        ; input maze pointer (later used as scratch byte value)
PTR         RN 3        ; running pointer over the matrix

NROW        RN 4
NCOL        RN 5
BASE        RN 6
LASTROW     RN 7
LASTCOL     RN 8
CURVAL      RN 9
NEWVAL      RN 10
CHANGED     RN 11
TMP1        RN 12       ; temp address for neighbor

UNVIS       EQU 0xFF    ; we convert ' ' (space) passages to 0xFF to avoid collision with value 32


; ------------------------------------------------------------
; int shortestPath(int rows=r0, int cols=r1, char* maze=r2)
; return r0 = length of shortest path (iterations), or 0 if not found
; ------------------------------------------------------------
shortestPath2 PROC
        EXPORT  shortestPath2

        PUSH    {r4-r11, lr}

        MOV     NROW, ROW
        MOV     NCOL, COL
        MOV     BASE, MAZE

        SUB     LASTROW, NROW, #1
        SUB     LASTCOL, NCOL, #1

; ========= Preprocess: convert ' ' passages to UNVIS (0xFF) =========
        MOV     ROW, #0
        MOV     PTR, BASE

pp_row_loop
        CMP     ROW, NROW
        BEQ     pp_done

        MOV     COL, #0
pp_col_loop
        CMP     COL, NCOL
        BEQ     pp_next_row

        LDRB    MAZE, [PTR]
        CMP     MAZE, #' '
        BNE     pp_skip
        MOV     MAZE, #UNVIS
        STRB    MAZE, [PTR]

pp_skip
        ADD     COL, COL, #1
        ADD     PTR, PTR, #1
        B       pp_col_loop

pp_next_row
        ADD     ROW, ROW, #1
        B       pp_row_loop

pp_done

; ========= Wavefront iterations =========
        MOV     CURVAL, #0            ; start from exit value 0

outer_loop
        ADD     NEWVAL, CURVAL, #1
        MOV     CHANGED, #0

        MOV     ROW, #0
        MOV     PTR, BASE

row_loop
        CMP     ROW, NROW
        BEQ     after_scan

        MOV     COL, #0

col_loop
        CMP     COL, NCOL
        BEQ     next_row

        LDRB    MAZE, [PTR]
        CMP     MAZE, CURVAL
        BNE     skip_cell

; ---------- RIGHT ----------
        CMP     COL, LASTCOL
        BEQ     check_left
        ADD     TMP1, PTR, #1
        LDRB    MAZE, [TMP1]
        CMP     MAZE, #'e'
        BEQ     found_path
        CMP     MAZE, #UNVIS
        BNE     check_left
        STRB    NEWVAL, [TMP1]
        MOV     CHANGED, #1

; ---------- LEFT ----------
check_left
        CMP     COL, #0
        BEQ     check_down
        SUB     TMP1, PTR, #1
        LDRB    MAZE, [TMP1]
        CMP     MAZE, #'e'
        BEQ     found_path
        CMP     MAZE, #UNVIS
        BNE     check_down
        STRB    NEWVAL, [TMP1]
        MOV     CHANGED, #1

; ---------- DOWN ----------
check_down
        CMP     ROW, LASTROW
        BEQ     check_up
        ADD     TMP1, PTR, NCOL        ; ptr + cols
        LDRB    MAZE, [TMP1]
        CMP     MAZE, #'e'
        BEQ     found_path
        CMP     MAZE, #UNVIS
        BNE     check_up
        STRB    NEWVAL, [TMP1]
        MOV     CHANGED, #1

; ---------- UP ----------
check_up
        CMP     ROW, #0
        BEQ     skip_cell
        SUB     TMP1, PTR, NCOL        ; ptr - cols
        LDRB    MAZE, [TMP1]
        CMP     MAZE, #'e'
        BEQ     found_path
        CMP     MAZE, #UNVIS
        BNE     skip_cell
        STRB    NEWVAL, [TMP1]
        MOV     CHANGED, #1

; ---------- advance ----------
skip_cell
        ADD     COL, COL, #1
        ADD     PTR, PTR, #1
        B       col_loop

next_row
        ADD     ROW, ROW, #1
        B       row_loop

after_scan
        CMP     CHANGED, #0
        BEQ     no_path

        ADD     CURVAL, CURVAL, #1
        B       outer_loop

found_path
        MOV     ROW, NEWVAL            ; return in r0
        POP     {r4-r11, pc}

no_path
        MOV     ROW, #0
        POP     {r4-r11, pc}

        ENDP
        END
