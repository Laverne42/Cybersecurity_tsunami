#include <stdio.h>
#include <windows.h>

int main () {

//En lenguaje ensamblador llamamos a la librería msvcrt.dll

    __asm{

        push ebp // Metemos la dirección de EBP en la pila
        mov ebp,esp // Mueve la base de la pila a la parte superior
        xor edi,edi // Cuando a un valor se le hace XOR a sí mismo, da 0
        push edi // Metemos 00000000 en la pila
        sub esp,0Ch // Sustrae a ESP 12 bytes
        mov byte ptr [ebp-0bh],6Dh // Mete "m" en hexadecimal en EBP -11 bytes (EBP -> base de la pila)
        mov byte ptr [ebp-0ah],73h // Mete "s" en EBP -10 bytes
        mov byte ptr [ebp-09h],76h // Mete "v" en EBP -9 bytes
        mov byte ptr [ebp-08h],63h // Mete "c" en EBP -8 bytes
        mov byte ptr [ebp-07h],72h // Mete "r" en EBP -7 bytes
        mov byte ptr [ebp-06h],74h // Mete "t" en EBP -6 bytes
        mov byte ptr [ebp-05h],2Eh // Mete "." en EBP -5 bytes
        mov byte ptr [ebp-04h],64h // Mete "d" en EBP -4 bytes
        mov byte ptr [ebp-03h],6Ch // Mete "l" en EBP -3 bytes
        mov byte ptr [ebp-02h],6Ch // Mete "l" en EBP -2 bytes
        lea eax,[ebp-0bh] // Cargamos en eax la dirección de ebp-11
        push eax // Metemos la dirección de "msvcrt.dll" en la pila
        mov ebx,0x7c801d7b // Metemos en ebx el valor del offset de system en msvcrt.dll (EBX -> registro base, se utiliza como handler de ficheros, direcciones de memoria...)
        call ebx // Llamamos a system y se ejecuta el shellcode

        // mov ebx,0x7c801d7b -> el offset de LoadLibraryA en kernel32.dll (al revés)

        push ebp
        mov ebp,esp
        xor edi,edi
        push edi
        sub esp,08h
        mov byte ptr [ebp-09h],63h
        mov byte ptr [ebp-08h],61h
        mov byte ptr [ebp-07h],6Ch
        mov byte ptr [ebp-06h],63h
        mov byte ptr [ebp-05h],2Eh
        mov byte ptr [ebp-04h],65h
        mov byte ptr [ebp-03h],78h
        mov byte ptr [ebp-02h],65h
        lea eax,[ebp-09h]
        push eax
        mov ebx,0x77c293c7
        call ebx
        }
    // mov ebx,0x77c293c7 -> el offset de system en msvcrt.dll
    
    }
