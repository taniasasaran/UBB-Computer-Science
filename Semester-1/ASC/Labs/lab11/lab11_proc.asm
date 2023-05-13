bits 32                         
segment code use32 public code
global compare_b

; procedure definition
    compare_b:
        mov eax, [esp+4]
        cmp al, 'b'
        je gasit
        mov eax, 0
        ret
        gasit: 
        mov eax, 1
        ret 