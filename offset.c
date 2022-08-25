#include <stdio.h>
#include <windows.h>
typedef VOID (*MYPROC)(LPTSTR);

int main (int argc, char **argv)
{
    char dll[100];
    char function[100];

    HINSTANCE library;
    MYPROC procadd;

    printf("Busca offsets. Introduce como primer argumento el nombre de la DLL,\n");
    printf("Por ejemplo %s msvcrt.dll system\n\n", argv[0]);

    if (argc !=3)
    {
        printf ("Introduce dos argumentos\n");
    }

    memset(dll,0,sizeof(dll));
    memset(function,0,sizeof(function));

    memcpy (dll, argv[1], strlen(argv[1]));
    memcpy (function, argv[2], strlen(argv[2]));

    library = LoadLibrary(dll);
    procadd = (MYPROC)GetProcAddress (library, function);

    printf("Offset de %s en la DLL %s es %x", function, dll, procadd);

    return 0;

}
