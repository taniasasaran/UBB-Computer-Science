bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 0101001011100101b
    b dw 0010111001101101b
    c dd 0

; our code starts here
segment code use32 class=code
    start:
        mov DX, 0
        mov AX, 0 ;we compute the result on DX:AX
        
        or AX, 0000000000111000b ; we initialize the bits 0-2 with 0 and the bits 3-5 with 1
        
        mov BX, [a] ;we put the value of A on BX
        and BX, 0111100000000000b ;we save the bits 11-14 of A 
        mov CL, 5 ; we put in CL the number bits we want to rotate
        ror BX, CL ;we rotate the number from BX with 5 bits to the right
        or AX, BX ; we put the 11-14 bits of A to the 6-9 bits of C(in BX)
        
        mov BX, [b] ;we put the value of B on BX
        and BX, 0000000001111110b ;we save the bits 1-6 of B
        mov CL, 9 ; we put in CL the number bits we want to rotate
        rol BX, CL ;we rotate the number from BX with 9 bits to the left
        or AX, BX ; we put the 1-6 bits of B to the 10-15 bits of C(in BX)
        
        or DX, 1111111111111111b ; we put 1 on the bits 16-31 of C
        
        mov [c], AX ; we move the low part of C in the first word of its address
        mov [c+2], DX ; we move the high part of C in the second word of its address
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

        
;    Given the words A and B, compute the doubleword C as follows:
;the bits 0-2 of C have the value 0
;the bits 3-5 of C have the value 1
;the bits 6-9 of C are the same as the bits 11-14 of A
;the bits 10-15 of C are the same as the bits 1-6 of B
;the bits 16-31 of C have the value 1

; C= 1111 1111 1111 1111 BBBB BBAA AA11 1000
; C= 1111 1111 1111 1111 1101 1010 1011 1000 = ff ff da b8
