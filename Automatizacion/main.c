#include <stdio.h>
#include <raylib.h>
#include <string.h>
#include "functions.h"

#define MAX_INPUT_CHARS 100

int main ()
{
    char phrasePointer[MAX_INPUT_CHARS];
    char addressPointer[MAX_INPUT_CHARS];
    getPhraseAndAddress(phrasePointer, addressPointer);
    
    algoritmoTrejos(phrasePointer, addressPointer);

    printResults();
    return 0;
}