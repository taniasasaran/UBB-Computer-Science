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
    S dd 12345607h, 1A2B3C15h
    lenS equ $-S       ;lenS=number of bytes of S
    D times lenS db -1
    
;Given an array S of doublewords, build the array of bytes D formed from bytes of doublewords sorted as unsigned numbers in descending order.
    
; our code starts here
segment code use32 class=code
    start:
        mov ecx, lenS   ;put the counter(length of S) in ecx
        jecxz done      ;compared ecx with zero; if ecx=0, then it skipped until the label "done" 
        mov esi, S      
        mov edi, D      ;put the source and the destination arrays' offsets in esi and edi
        cld             ;cleared the DF so we go from left to right 
        
;IDEA
; trec prin toti bytes si il caut pe cel  mai mare
; pun 0 in ah si tot iau bytes in al pe care ii compar cu ah si daca al>ah, inlocuiesc ah cu al
; cand ajung la capatul sirului, pun ce aveam in ah in sirul D si inlocuiesc max din sir cu 0
; repet de lenS (nr de bytes)

        repeta1:
            push ecx
            push esi
            push edi    ;pushed the values from ecx, esi and edi in the stack to save them for later use
            mov ah, 0   ;put 0 in ah
            mov ecx, lenS   ;put the counter(length of S) in ecx
            repeta2:
                lodsb            ;put each byte in al
                cmp al, ah       ;compared ah with al
                jbe next         ;if al<=ah, jump to "next:" label
                mov ah, al       ;otherwise, copy in ah the value from al
                mov ebx, esi     
                dec ebx          ;and store the offset of that byte into ebx (ebx-- because lodsb produces esi++)
                next:            
            LOOP repeta2   ;this loop finds the greatest byte from the array
            mov al, 0      ;put 0 in al so it could be transferred in memory
            mov edi, ebx   ;put the offset of the max number of array into edi
            stosb          ;change the max value of array (in memory) to 0 (so it wont be analyzed again)
            pop edi        
            pop esi
            pop ecx        ;recover the initial values of edi, esi and ecx from stack
            mov al, ah     ;put the max value found (stored in ah) in al
            stosb          ;transfer the max value found in the destination array
        LOOP repeta1   ;this loop writes in destination array each greatest byte of the source array(and puts 0 in the source array)
        
        done:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
