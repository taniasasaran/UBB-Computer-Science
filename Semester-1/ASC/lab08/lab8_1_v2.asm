bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf            
import exit msvcrt.dll     
import printf msvcrt.dll     ; indicating to the assembler that the printf fct can be found in the msvcrt.dll library
import scanf msvcrt.dll 

; our data is declared here (the variables needed by our program)
segment  data use32 class=data
	a dd 0       ; rezervam un spatiu de un doubleword pt a, pe care il initializam cu 0
    b dd 0       ; rezervam un spatiu de un doubleword pt b, pe care il initializam cu 0
	message  db "Suma lui a=%d(decimal) si a lui b=%d(decimal) este s=%x(hexadecimal)", 0  ;mesajul ce se va printa pe ecran, sir de caractere(bytes) si la fiecare variabila specificam tipul de data(baza in care afisam)
	format  db "%d", 0  ; %d <=> a decimal number (base 10), formatul numerelor citite din consola

    
segment  code use32 class=code
    start:
                                               
        ; calling scanf(format, n) => we read the number and store it in the variable n
        ; push parameters on the stack from right to left
        push  dword a       ; adresa lui a, nu valoarea
        push  dword format  ; formatul in care vrem sa citim valoarea
        call  [scanf]       ; call scanf pentru citire
        add  esp, 4 * 2     ; eliberam stackul de valorile introduse; 4 = dimesiunea unui dword; 2 = numarul de parametri
        
        push  dword b       ; adresa lui b, nu valoarea
        push  dword format  ; formatul in care vrem sa citim valoarea
        call  [scanf]       ; call scanf pentru citire
        add  esp, 4 * 2     ; eliberam stackul de valorile introduse; 4 = dimesiunea unui dword; 2 = numarul de parametri
        mov eax, [a]        ; punem in eax un dword de la adresa lui a, adica exact valoarea lui a
        add eax, [b]        ; adaugam in eax un dword de la adresa lui b, adica exact valoarea lui b
        ; in eax avem stocata valoarea sumei dintre a si b
        
        ; print the message and the value of the sum
        push  eax
        push dword [b]
        push dword [a]
        push  dword message ; push parameters on the stack from right to left
        call  [printf]      ; call printf pentru afisare
        add  esp,4*4        ; eliberam stackul de valorile introduse; 4 = dimesiunea unui dword; 4 = numarul de parametri
        
        ; exit(0)
        push  dword 0       ; push the parameter for exit on the stack
        call  [exit] 