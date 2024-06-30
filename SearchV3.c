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

// Función para buscar una palabra o frase en una línea de texto (ignorando mayúsculas/minúsculas y tildes)
int search_phrase_in_line(const char *line, const char *phrase) {
    char *line_processed = remove_accents_and_tolower(line); // Procesar la línea
    if (line_processed == NULL) {
        perror("Error al procesar la línea");
        return 0; // Retorna 0 si falla el procesamiento
    }

    char *phrase_processed = remove_accents_and_tolower(phrase); // Procesar la frase
    if (phrase_processed == NULL) {
        perror("Error al procesar la frase");
        free(line_processed);
        return 0; // Retorna 0 si falla el procesamiento
    }

    // Buscar la frase en la línea procesada
    char *result = strstr(line_processed, phrase_processed);

    free(line_processed);
    free(phrase_processed);

    if (result != NULL) {
        return 1;
    }
    return 0;
}

// Función para leer el contenido de un archivo en una cadena
char* read_file_to_string(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(length + 1);
    if (buffer == NULL) {
        perror("Error al asignar memoria");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}

// Función principal que recibe punteros para la frase y el archivo de texto
void search_phrase_in_file(const char *frase, const char *texto_extraido) {
    const char *output_filename = "FinalSearch.txt"; //Las lineas encontradas son almacenadas en FinalSearch.txt

    // Abrir el archivo de texto para escritura
    FILE *output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        perror("Error al abrir el archivo de salida");
        return;
    }

    // Copiar el contenido del texto extraído a un buffer modificable
    char *texto_copy = strdup(texto_extraido);
    if (texto_copy == NULL) {
        perror("Error al asignar memoria");
        fclose(output_file);
        return;
    }

    char *line = strtok(texto_copy, "\n"); // Suponiendo que el texto extraído está separado por líneas

    // Recorrer todas las líneas del texto extraído
    while (line != NULL) {
        // Buscar la frase en la línea actual
        if (search_phrase_in_line(line, frase)) {
            // Escribir la línea en el archivo de salida si se encuentra la frase
            fprintf(output_file, "%s\n", line);
        }
        line = strtok(NULL, "\n"); // Obtener la siguiente línea
    }

    free(texto_copy);
    fclose(output_file);
}

// Función para buscar la frase en el archivo de texto
void searchPhrase(char *frase, char *archivo_texto) {
    // Leer el contenido del archivo de texto
    char *texto_extraido = read_file_to_string(archivo_texto);
    if (texto_extraido == NULL) {
        return;
    }

    // Llamar a la función que busca la frase en el texto extraído
    search_phrase_in_file(frase, texto_extraido);

    free(texto_extraido);
}

int main() {
    char frase[] = "Frase que desea buscar";
    char archivo_texto[] = "archivo.txt que desee"; // este archivo debe existir en el mismo directorio

    // Llama a la función que maneja la búsqueda de la frase
    searchPhrase(frase, archivo_texto);

    return 0;
}


/*
Este código en C está diseñado para buscar una frase específica dentro de un texto extraído de un archivo. 
El código originalmente espera recibir la frase a buscar y el contenido del archivo de texto a través de punteros provenientes de otro código relacionado al proyecto.
Por ende, en este caso se le agregaron ciertas funciones para comprobar su correcta funcionalidad

Funciones agregadas: 
    1) read_file_to_string: 
    Tiene como objetivo analizar el archivo de texto ingresado en main.
    Se puede decir que "convierte el texto en un puntero" en el sentido de que lee el contenido del archivo de texto y devuelve un puntero (char*) que apunta a una cadena que contiene ese texto en memoria dinámica. 
    Dicho puntero se puede usar posteriormente en el programa para acceder y manipular el contenido del archivo.
    
    
    2) main
    Su funcionalidad radica en que define una frase y el nombre de un archivo de texto. 
    Luego llama a searchPhrase pasándoles estos valores, searchPhrase espera recibir estos valores como punteros (char*).

Agregar estas funciones fue necesario para poder recrear una frase y un archivo en el cual buscar dicha frase.

*/

