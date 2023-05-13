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
    a db 100
    b dw 50
    c dd -110
    
;c+a+b+b+a ,  a - byte, b - word, c - double word, d - qword

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ECX, [c] ;we put the doubleword c in ECX register
        mov AL, [a]
        cbw
        cwde    ; we put the byte a in the AL register and converted it into EAX
        add ECX, EAX ;we computed c+a and stored the result in ECX
        mov EBX, EAX ;we stored the value of a in the EBX register so we wont have to repeat the above steps (lines 25-27)
        mov AX, [b] 
        cwde    ; we put the word b in the AX register and converted it into EAX
        adc ECX, EAX  
        adc ECX, EAX
        adc ECX, EBX ;we computed addition with carry between registers in which... 
                     ; ...we have stored the a&b(EBX&EAX respectively) variables and the result(ECX)
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
