org 100h

.DATA
    input_string DB 'We are IUT Students', 0Dh, 0Ah, '$'

.CODE  
    
MAIN PROC
    mov ax, @DATA
    mov ds, ax   
    
    lea si, input_string
    mov cx, 18
    
lower_loop:
    mov al, [si]
    
    cmp al, 'A'
    jle skip
    cmp al, 'Z'
    jge skip            
    
    add al, 20h
    mov [si], al 
    
    
skip:
    inc si
    loop lower_loop  
    
    mov ah, 09h
    lea dx, input_string
    int 21h  
    
    mov ah, 01h
    int 21h
    mov bl, al
    
    
    lea si, input_string
    mov cx, 18
    mov dl, 0    
    
count:
    mov al, [si]
    
    cmp al, bl
    jne skip_again
    
    inc dl
    
skip_again:
    inc si
    loop count
         
         
    add dl, 30h                     
    mov ah, 02h
    int 21h
    
    mov ah, 4ch
    int 21h
    
MAIN ENDP
END MAIN
RET