bits 32 ; assembling for the 32 bits architecture
    

;Read a string of unsigned numbers in base 10 from keyboard. Determine the maximum value of the string and write it in the file max.txt (it will be created) in 16  base.
    
; our code starts here
segment code use32 class=code
global _maximumValue
    _maximumValue:
        mov edx, 0
        cld
        mov ecx, [esp+8]
        mov esi, [esp+4]
        loop_citire:
            lodsd
            cmp eax, edx
            jbe next
            mov edx, eax
            next:
        loop loop_citire
        mov eax, edx
        ret 
    