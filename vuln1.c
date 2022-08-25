#include <stdio.h>
#include <string.h> 

int main(int argc, char **argv)
{
    char buffer[64]; 
    if (argc < 2)
        {  
        printf ("Introduce un argumento\n"); 
        return 0;  
        }
    strcpy (buffer, argv[1]); 
    return 0;  

}