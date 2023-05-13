bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 3
    b db 3
    c db 3
    e dd 3
    x dq 3
    
;x-(a*b*25+c*3)/(a+b)+e; a,b,c-byte; e-doubleword; x-qword

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov edx, 0
        mov al, [a]
        mov bl, [b]
        imul bl    ; a*b is in AX
        mov bx, 25
        imul bx    ; a*b*25 is in EAX
        mov ecx, eax  ; we moved our result in ECX so we can free the EAX and use it later on
        mov al, [c]
        mov bl, 3
        imul bl    ; c*3 found in AX
        cwde      ; we converted a word to a dword so from AX to EAX
        add ecx, eax  ; a*b*25+c*3 found in ECX
        
        mov al, [a]
        add al, [b]   ; a+b is in AL
        cbw      ; we converted a byte to a word so from AL to AX
        mov BX, AX    ; we moved our result in BX so we can free the AX and use it later on
        mov EAX, 0
        mov EDX, 0    ; we eliminated all the data stored in EDX and EAX
        push ECX
        pop AX
        pop DX   ; we "converted" ECX to DX:AX
        idiv BX  ; the (a*b*25+c*3)/(a+b) result is found in AX
        cwde          
        cdq           ; we converted a word to a quadword so from AX to EDX:EAX
        
        ;mov EBX:ECX, qword[x]
        mov ECX, dword[x]
        mov EBX, dword[x+4]
        ;sub EBX:ECX, EDX:EAX
        sub ECX, EAX
        sbb EBX, EDX  ;result found in EBX:ECX
        
        mov EAX, [e]
        cdq      ; we converted a dword to a qword so from EAX to EDX:EAX
        
        ;add EAX:EDX, EBX:ECX
        add EDX, ECX
        adc EAX, EBX
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
