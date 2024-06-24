#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para tolower()

// Definir ssize_t
#ifndef _SSIZE_T_DEFINED
typedef long ssize_t;
#define _SSIZE_T_DEFINED
#endif

// Función para eliminar tildes y convertir a minúsculas
char *remove_accents_and_tolower(const char *str) {
    char *result = malloc(strlen(str) + 1);
    if (result == NULL) {
        perror("Error al asignar memoria");
        return NULL;
    }

    int i = 0;
    while (str[i]) {
        switch (str[i]) {
            case 'á': result[i] = 'a'; break;
            case 'é': result[i] = 'e'; break;
            case 'í': result[i] = 'i'; break;
            case 'ó': result[i] = 'o'; break;
            case 'ú': result[i] = 'u'; break;
            case 'Á': result[i] = 'a'; break;
            case 'É': result[i] = 'e'; break;
            case 'Í': result[i] = 'i'; break;
            case 'Ó': result[i] = 'o'; break;
            case 'Ú': result[i] = 'u'; break;
            case 'ñ': result[i] = 'n'; break;
            case 'Ñ': result[i] = 'n'; break;
            default: result[i] = tolower((unsigned char)str[i]);
        }
        i++;
    }
    result[i] = '\0';

    return result;
}

// Función para buscar una palabra en una línea de texto (ignorando mayúsculas/minúsculas y tildes)
int search_word_in_line(const char *line, const char *word) {
    char *line_processed = remove_accents_and_tolower(line); // Procesar la línea
    if (line_processed == NULL) {
        perror("Error al procesar la línea");
        return 0; // Retorna 0 si falla el procesamiento
    }

    char *word_processed = remove_accents_and_tolower(word); // Procesar la palabra
    if (word_processed == NULL) {
        perror("Error al procesar la palabra");
        free(line_processed);
        return 0; // Retorna 0 si falla el procesamiento
    }

    // Buscar la palabra en la línea procesada
    char *result = strstr(line_processed, word_processed);

    free(line_processed);
    free(word_processed);

    if (result != NULL) {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    // Verificar que el número de argumentos sea correcto
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <palabra_a_buscar> <archivo.txt>\n", argv[0]);
        return 1;
    }

    const char *word = argv[1];
    const char *filename = argv[2];

    // Abrir el archivo de texto
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int line_number = 0;

    // Leer el archivo línea por línea
    while ((read = getline(&line, &len, file)) != -1) {
        line_number++;
        // Buscar la palabra en la línea actual (ignorando diferencias de mayúsculas/minúsculas y tildes)
        if (search_word_in_line(line, word)) {
            printf("Línea %d: %s", line_number, line);
        }
    }

    free(line);
    fclose(file);

    return 0;
}