bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; a-b-d+2+c+(10-b)

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 78
    b db 5
    c db 20
    d db 24

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov AX, [a]
        mov BX, [b]
        sub AX, BX
        mov BX, [d]
        sub AX, BX
        mov BX, [c]
        add BX, 2
        ADD AX, BX
        mov BX, 10
        mov CX, [b]
        sub BX, CX
        add AX, BX
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
