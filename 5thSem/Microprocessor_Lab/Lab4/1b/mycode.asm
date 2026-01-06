org 100h

.DATA
    ODD_SUM dw 0                    
    EVEN_SUM dw 0                   
    input_val db 0                  
    digit_array db 6 dup(0)        ; Array to store digits
    
    msg_input db 'Enter the value of N (2-9): $'
    msg_odd db 0Dh, 0Ah, 'ODD_SUM: $'
    msg_even db 0Dh, 0Ah, 'EVEN_SUM: $'
    
.CODE
MAIN PROC
    mov ax, @DATA
    mov ds, ax
    
    ; Display input prompt
    mov dx, OFFSET msg_input
    mov ah, 09h
    int 21h
    
    ; Take input
    mov ah, 01h
    int 21h
    sub al, 48                      
    mov input_val, al
    
    ; Calculate ODD_SUM
    xor cx, cx
    mov cl, input_val               
    mov bx, 1                       
    mov si, 0                       
    
ODD_LOOP:
    mov ax, bx                      
    mul bx                          
    add si, ax                      
    add bx, 2                       
    loop ODD_LOOP
    
    mov ODD_SUM, si                 
    
    ; Calculate EVEN_SUM
    xor cx, cx
    mov cl, input_val               
    mov bx, 2                       
    mov di, 0                       
    
EVEN_LOOP:
    mov ax, bx                      
    mul bx                          
    add di, ax                      
    add bx, 2                       
    loop EVEN_LOOP
    
    mov EVEN_SUM, di                
    
    ; Display ODD_SUM
    mov dx, OFFSET msg_odd
    mov ah, 09h
    int 21h
    
    mov ax, ODD_SUM
    call PRINT_NUMBER
    
    ; Display EVEN_SUM
    mov dx, OFFSET msg_even
    mov ah, 09h
    int 21h
    
    mov ax, EVEN_SUM
    call PRINT_NUMBER
    
    ; Exit program
    mov ah, 4Ch
    int 21h
    
MAIN ENDP

PRINT_NUMBER PROC
    mov bx, 10
    xor cx, cx
    mov si, OFFSET digit_array
    
    ; Special case for 0
    cmp ax, 0
    jne EXTRACT_DIGITS
    mov dl, '0'
    mov ah, 02h
    int 21h
    ret
    
EXTRACT_DIGITS:
    xor dx, dx
    div bx  ; quotient goes in AX and remainder goes in DX                        
    add dl, 48                      
    mov [si], dl                    
    inc si
    inc cx
    cmp ax, 0
    jne EXTRACT_DIGITS
    
    ; Print digits in reverse order
    dec si
PRINT_DIGITS:
    mov dl, [si]
    mov ah, 02h
    int 21h
    dec si
    loop PRINT_DIGITS
    
    ret
PRINT_NUMBER ENDP

END MAIN