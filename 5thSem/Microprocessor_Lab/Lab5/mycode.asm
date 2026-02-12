.MODEL SMALL
.STACK 100H

.DATA
    NUMBERS DB 5 DUP(?)   ; ARRAY
    AVERAGE DB ?
    LARGEST DB ?
    SMALLEST DB ?
    
    MSG_INPUT DB 'Enter 5 digits: $'
    MSG_AVG DB 'AVERAGE: $'
    MSG_LARGEST DB 'LARGEST: $'
    
.CODE 
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX
    
    ;PROMPT
    LEA DX, MSG_INPUT
    MOV AH, 09
    INT 21H
    
    ;READ 5 DIGITS
    LEA SI, NUMBERS   ; POINT SI TO THE FIRST ELEMENT IN THE NUMBERS
    MOV CX, 5
    
READ_LOOP:
    MOV AH, 01H ; INPUT
    INT 21H
    
    SUB AL, '0' ; ASCII -> DECIMAL
    MOV [SI], AL
    INC SI
    LOOP READ_LOOP    
    
    ; CALL PROCEDURES
    CALL CALC_AVG
    CALL FIND_LARGEST 
    
    ; PRINT AVERAGE
    LEA DX, MSG_AVG
    MOV AH, 09H
    INT 21H

    MOV DL, AVERAGE
    MOV AH, 02H
    INT 21H

    ; PRINT LARGEST
    LEA DX, MSG_LARGEST
    MOV AH, 09H
    INT 21H

    MOV DL, LARGEST
    MOV AH, 02H
    INT 21H

    ; Exit program
    MOV AH, 4CH
    INT 21H
MAIN ENDP


;---------------------
; CALCULATE AVERAGE
;---------------------
CALC_AVG PROC   
    LEA SI, NUMBERS
    MOV CX, 5
    XOR AX, AX    ; AH, AL BECOMES 0
    
SUM_LOOP:
    ADD AL, [SI]
    INC SI
    LOOP SUM_LOOP
    
    MOV BL, 5
    DIV BL   
    ADD AL, '0'
    MOV AVERAGE, AL
    RET 
CALC_AVG ENDP

;---------------------
; FIND LARGEST
;---------------------
FIND_LARGEST PROC
    LEA SI, NUMBERS
    MOV AL, [SI]
    MOV CX, 4
    INC SI
    
LARGE_LOOP:
    CMP AL, [SI]
    JGE NEXT_L
    MOV AL, [SI]

NEXT_L:
    INC SI
    LOOP LARGE_LOOP
    
    ADD AL, '0'
    MOV LARGEST, AL
    RET
FIND_LARGEST ENDP

END MAIN


    
    
    