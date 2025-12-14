ORG 100h
START:

; --- Input a single letter ---
MOV AH, 1        ; DOS function 1: single key input
INT 21h          ; AL = ASCII of input letter

; --- Save original input ---
MOV BL, AL       ; BL = original letter

; --- Determine opposite case ---
CMP AL, 'A'
JL CONVERT_LOWER ; If < 'A', it's lowercase
CMP AL, 'Z'
JG CONVERT_LOWER ; If > 'Z', it's lowercase
; else uppercase ? convert to lowercase
CONVERT_UPPER:
    ADD AL, 20h
    JMP NEXT_STEP

CONVERT_LOWER:      ; lowercase ? convert to uppercase
    SUB AL, 20h

NEXT_STEP:
    MOV CL, AL     ; CL = converted letter

; --- Print next 5 letters in opposite case ---
MOV DH, 5         ; DH = counter for next letters
NEXT_LOOP:
    INC CL
    ; Wrap around if needed (A-Z or a-z)
    CMP BL, 'A'   ; Check if input was uppercase
    JL INPUT_LOWER
    CMP CL, 'Z'
    JG WRAP_NEXT_UPPER
    JMP PRINT_NEXT

INPUT_LOWER:
    CMP CL, 'z'
    JG WRAP_NEXT_LOWER
    JMP PRINT_NEXT

WRAP_NEXT_UPPER:
    MOV CL, 'A'
    JMP PRINT_NEXT

WRAP_NEXT_LOWER:
    MOV CL, 'a'

PRINT_NEXT:
    MOV AH, 2
    MOV DL, CL
    INT 21h
    DEC DH
    JNZ NEXT_LOOP

; --- Move to new line ---
MOV AH, 2
MOV DL, 0Dh
INT 21h
MOV DL, 0Ah
INT 21h

; --- Print previous 5 letters in opposite case ---
MOV CL, AL     ; CL = converted input
MOV DH, 5      ; counter
PREV_LOOP:
    DEC CL
    ; Wrap around if needed
    CMP BL, 'A'
    JL PREV_LOWER
    CMP CL, 'A'
    JL WRAP_PREV_UPPER
    JMP PRINT_PREV

PREV_LOWER:
    CMP CL, 'a'
    JL WRAP_PREV_LOWER
    JMP PRINT_PREV

WRAP_PREV_UPPER:
    MOV CL, 'Z'
    JMP PRINT_PREV

WRAP_PREV_LOWER:
    MOV CL, 'z'

PRINT_PREV:
    MOV AH, 2
    MOV DL, CL
    INT 21h
    DEC DH
    JNZ PREV_LOOP

; --- Terminate program ---
MOV AH, 4Ch
INT 21h

END START
