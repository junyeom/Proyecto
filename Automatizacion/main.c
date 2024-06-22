#include <stdio.h>
#include <raylib.h>
#include <string.h>
#include "functions.h"

#define MAX_INPUT_CHARS     20
#define MAX_OUTPUT_CHARS     40

int main ()
{
    char frase[MAX_INPUT_CHARS];
    char direccion[MAX_INPUT_CHARS];
    getPhraseAndAddress(frase, direccion);

    char resultado1[MAX_OUTPUT_CHARS];
    char resultado2[MAX_OUTPUT_CHARS];
    int resultado3;
    searchPhrase(frase, direccion, resultado1, resultado2, &resultado3);
    
    printResults(resultado1, resultado2, &resultado3);
    return 0;
}