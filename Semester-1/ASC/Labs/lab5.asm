bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    A db 2, 1, 3, 3, 4, 2, 6
    LA equ $-A
    B db 4, 5, 7, 6, 2, 1
    LB equ $-B
    LR equ LA+LB
    R times LR db 0

;Two byte strings A and B are given. Obtain the string R by concatenating the elements of B in ;reverse order and the odd elements of A.
;Example:
;A: 2, 1, 3, 3, 4, 2, 6
;B: 4, 5, 7, 6, 2, 1
;R: 1, 2, 6, 7, 5, 4, 1, 3, 3    

; our code starts here
segment code use32 class=code
    start:
        stringB:
            mov ecx, LB    ;we move the length of B in ecx so we can create a loop
            jecxz stringA  ;if ecx is 0, we jump to the stringA label and prevent entering the repeta1 loop
            mov esi, R-1   ; we move the address of the last element of B in esi
            mov edi, R     ; we move the address of the first element of R in edi
            repeta1:
                std       ;we will go from high to small addresses, therefore we set the direction flag to 1 and esi will dencrement
                lodsb     ;we move the element from the esi address into AL and dec(esi)
                cld       ;we will go from small to high addresses, therefore we set the direction flag to 0 and edi will increment
                stosb     ;we move the element from AL to the edi address and inc(edi)
            LOOP repeta1      ;we repeat this process a number of ecx of times, which is equal to the length of B
            
        stringA:
            mov ecx, LA       ;we move the length of A in ecx so we can create a loop
            jecxz sfarsit     ;if ecx is 0, we jump to the 'sfarsit' label and prevent entering the repeta2 loop
            mov esi, A        ; we move the address of the first element of A in esi
            mov edi, R+LB ;this is optional   ; in edi we move the address of the LBth element of R    
            cld               ;we will go from small to high addresses, so we set the direction flag to 0, edi and esi will increment
            repeta2:
                lodsb     ;we move the element from the esi address into AL and dec(esi)
                mov bl, al    ;we copy the number from AL to BL because we will need it after some operations which will modify it
                and bl, 00000001b  ;we save the last digit of the element which will be 0 or 1, depending on the element's parity
                cmp bl, 0     ;we compare BL with 0; if the element was even, then BL=0, then zf=1; otherwise BL=1 and zf=0
                jz done   ;if zf=0(the number is even), we jump to label 'done' and then search for another
                          ;if zf=1(the number is odd),  we move to the next instruction
                stosb     ;we move the element(odd number) from AL to the edi address and inc(edi)
                done:     ;this label helps get over the unwanted instructions
            LOOP repeta2   
        sfarsit:      ;this label helps get over the unwanted instructions and loops
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
