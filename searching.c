#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para tolower()

// Definir ssize_t
#ifndef _SSIZE_T_DEFINED
typedef long ssize_t;
#define _SSIZE_T_DEFINED
#endif


// Función para buscar una palabra en una línea de texto (ignorando mayúsculas/minúsculas)
int search_word_in_line(const char *line, const char *word) {
    char *line_lower = strdup(line); // Copiar la línea para no modificar la original
    if (line_lower == NULL) {
        perror("Error al duplicar la línea");
        return 0; // Retorna 0 si falla la duplicación
    }

    char *word_lower = strdup(word); // Copiar la palabra para no modificar la original
    if (word_lower == NULL) {
        perror("Error al duplicar la palabra");
        free(line_lower);
        return 0; // Retorna 0 si falla la duplicación
    }

    // Convertir la línea y la palabra a minúsculas
    for (int i = 0; line_lower[i]; i++) {
        line_lower[i] = tolower(line_lower[i]);
    }
    for (int i = 0; word_lower[i]; i++) {
        word_lower[i] = tolower(word_lower[i]);
    }

    // Buscar la palabra en la línea convertida a minúsculas
    char *result = strstr(line_lower, word_lower);

    free(line_lower);
    free(word_lower);

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
        // Buscar la palabra en la línea actual (ignorando diferencias de mayúsculas/minúsculas)
        if (search_word_in_line(line, word)) {
            printf("Línea %d: %s", line_number, line);
        }
    }

    free(line);
    fclose(file);

    return 0;
}