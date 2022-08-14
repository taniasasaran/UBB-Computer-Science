bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
          
extern compare_b       
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db '10100111b', '01100011b', '110b', '101011b'
    len_a equ $-a
    format db '%c', 0
    added_string db ', ', 0
    added_string_format db '%s', 0
    ecx_copy resd 1
    eax_copy resd 1

    ;A string containing n binary representations on 8 bits is given as a character string.
;Obtain the string containing the numbers corresponding to the given binary representations.
;Example:
;Given: '10100111b', '01100011b', '110b', '101011b'
;Obtain: 10100111b, 01100011b, 110b, 101011b
    
; our code starts here
segment code use32 public class=code
    start:
        mov ecx, len_a   ;ecx= length of the array (in bytes)
        jecxz final
        mov esi, a  ;esi= address of the array
        read_loop:
            mov [ecx_copy], ecx  ;save ecx in memory
            mov eax, 0
            lodsb  ;al='1'       ;eax= 0000 00xy where xy=ascii code of the character 0, 1 or b
            mov [eax_copy], eax  ;save eax in memory
            
            push eax
            push format
            call [printf]    ;print the character '0', '1', 'b'
            add esp, 4*2
            
            mov eax, [eax_copy]  ;restore the value of eax
            push eax
            call compare_b  ; call compare_b    a function that compares characters with 'b' 1 ont he stack if equal, else 0 on the stack (dword)
              
            cmp eax, 0    ;eax=1 if the character was b, else 0 
            jne print_string   ;if eax=1, print ', '
            jmp sfarsit  ;if eax=0, go to the end of the loop 
            
            print_string:
            cmp dword[ecx_copy], 1
            je sfarsit   ;if ecx_copy=1(aka it was the last element), go to the end of the loop
            push added_string    ;else, print ', '
            push added_string_format
            call [printf]
            add esp, 4*2
            
            sfarsit:
            mov ecx, [ecx_copy] ;restore the value of ecx
            loop read_loop      ;compare ecx with 0 and loop again if ecx!=0
        
        final: 
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
