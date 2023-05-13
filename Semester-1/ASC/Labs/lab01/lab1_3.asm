bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions


; (a*2)+2*(b-3)-d-2*c                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 50
    b db 9
    c db 5
    d dw 2

; our code starts here
segment code use32 class=code
    start:
        mov EAX, 0
        mov AL, [a]
        mov BL, 2
        mul BL
        mov DX, AX
        mov AL, [b]
        mov BL, 3
        sub AL, BL
        mov BL, 2
        mul BL
        add DX, AX
        mov BX, [d]
        sub DX, BX
        mov AL, [c]
        mov CL, 2
        mul CL
        sub DX, AX
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
