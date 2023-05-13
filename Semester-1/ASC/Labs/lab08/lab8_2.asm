bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, fprintf ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll     ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                           ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
                          
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    text db "$2405@TaNiA#31%0=&", 0
 
    len_text equ $-text-1 
    ;48-57, 65-90, 97-122
    file_name db "sir.txt", 0   ; filename to be created
    access_mode db "w", 0       ; file access mode:
                                ; w - creates an empty file for writing
    file_descriptor dd -1       ; variable to hold the file descriptor
    format_sir dd '%s', 0
    
;A file name and a text (defined in the data segment) are given. The text contains lowercase letters, uppercase letters, digits and special characters. Replace all the special characters from the given text with the character 'X'. Create a file with the given name and write the generated text to file.
    
; our code starts here
segment code use32 class=code
    start:
        push dword access_mode     ; open the file
        push dword file_name
        call [fopen]
        add esp, 4*2                ; clean-up the stack

        mov [file_descriptor], eax  ; store the file descriptor returned by fopen
        
        ; check if fopen() has successfully created the file (EAX != 0)
        cmp eax, 0
        je final_final
        
        mov esi, text
        mov edi, text  ;modific datele din memorie si atunci pun in esi=edi adresa sirului meu
        mov ecx, len_text  ;lungimea in ecx
        jecxz final
        cld
        loop1:
            lodsb   ;iau un caracter din sir
            cmp al, '0'  ;compar cu codul ascii a lui 0
            jb change    ;daca e mai mic, clar e caracter special si trebuie schimbat
            cmp al, '9'   ;compar cu codul ascii a lui 9
            ja uppercase1 ;daca e mai mare, poate fi caracter special, litera mare sau litera mica; jump la verificare litera mare
            back:  ;label de intoarcere in loop-ul de citire
            stosb  ;punem in memorie X sau acelasi caracter
        loop loop1
        
        jmp final  ;dupa ce am trecut prin toate elementele sirului, sarim la final peste label-uri
        
        uppercase1:
        cmp al, 65  ;compar cu codul ascii a lui A
        jb change    ;daca e mai mic,nu e cifra(verificat in loop) clar e caracter special si trebuie schimbat
        cmp al, 90  ;compar cu codul ascii a lui Z
        ja lowercase1 ;daca e mai mare, poate fi caracter special sau litera mica; jump la verificare litera mica
        jb back  ;ne intoarcem in loop dupa verificare
        
        lowercase1:
        cmp al, 97   ;compar cu codul ascii a lui a
        jb change     ;daca e mai mic,nu e cifra(verificat in loop), nici lit mare(de acolo venim) clar e caracter special si trebuie schimbat
        cmp al, 122  ;compar cu codul ascii a lui z
        ja change   ;daca e mai mare ca z, clar e caracter special si trebuie schimbat
        jb back   ;ne intoarcem in loop dupa verificare
        
        change:
        mov al, 'X' ;punem codul ascii a lui X in AL
        jmp back  ;ne intoarcem in loop
        
        mov eax, 0
        
        final:
        
        ;call fprintf to write in the file
        push dword text
        push dword format_sir
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*3
        
        ; call fclose() to close the file
        ; fclose(file_descriptor)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4

        final_final:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
