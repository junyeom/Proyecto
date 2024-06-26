#include <stdio.h>
#include <raylib.h>
#include <string.h>

#define MAX_OUTPUT_CHARS     40

void searchPhrase(char * frase, char * direccion, char * resultado1, char * resultado2, int * resultado3)
{
    if(frase!=NULL && direccion!=NULL)
    {
        strncpy(resultado1, "Este es el resultado 1", MAX_OUTPUT_CHARS);
        strncpy(resultado2, "Este es el resultado 2", MAX_OUTPUT_CHARS);
        *resultado3 = 4;
    }
}