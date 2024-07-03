#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <poppler/glib/poppler.h>
#include <glib.h>
#include <ctype.h>

// Función para eliminar tildes y convertir a minúsculas
char *remove_accents_and_tolower(char * phrasePointer) {
    char *result = malloc(strlen(phrasePointer) + 1);
    if (result == NULL) {
        perror("Error al asignar memoria");
        return NULL;
    }

    int i = 0;
    while (phrasePointer[i]) {
        switch (phrasePointer[i]) {
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
            default: result[i] = tolower((unsigned char)phrasePointer[i]);
        }
        i++;
    }
    result[i] = '\0';

    return result;
}

// Función para buscar una palabra o frase en una línea de texto (ignorando mayúsculas/minúsculas y tildes)
int search_phrase_in_line(const char *line, char * phrasePointer) {
    char *line_processed = remove_accents_and_tolower(line); // Procesar la línea
    if (line_processed == NULL) {
        perror("Error al procesar la línea");
        return 0; // Retorna 0 si falla el procesamiento
    }

    char *phrase_processed = remove_accents_and_tolower(phrasePointer); // Procesar la frase
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

void search_phrase_in_pdf(const char *pdf_path, char * phrasePointer, FILE *output_file) {
    char *uri = g_filename_to_uri(pdf_path, NULL, NULL);
    if (!uri) {
        fprintf(stderr, "Error al convertir la ruta a URI: %s\n", pdf_path);
        return;
    }

    GError *error = NULL;
    PopplerDocument *document = poppler_document_new_from_file(uri, NULL, &error);
    g_free(uri);
    if (!document) {
        fprintf(stderr, "Error al abrir el archivo %s: %s\n", pdf_path, error->message);
        g_error_free(error);
        return;
    }

    int num_pages = poppler_document_get_n_pages(document);
    int found_any = 0;

    for (int i = 0; i < num_pages; i++) {
        PopplerPage *page = poppler_document_get_page(document, i);
        if (page) {
            char *text = poppler_page_get_text(page);
            if (text) {
                char *line = strtok(text, "\n");
                int line_number = 1;
                while (line) {
                    if (search_phrase_in_line(line, phrasePointer)) {
                        if (!found_any) {
                            fprintf(output_file, "Archivo: %s\n", pdf_path);
                            found_any = 1;
                        }
                        fprintf(output_file, "Página: %d, Línea %d: %s\n", i + 1, line_number, line);
                    }
                    line = strtok(NULL, "\n");
                    line_number++;
                }
                g_free(text);
            }
            g_object_unref(page);
        }
    }

    g_object_unref(document);
}

void process_directory(char * phrasePointer, char * addressPointer, const char *output_filename) {
    DIR *dir = opendir(addressPointer);
    if (!dir) {
        perror("Error al abrir el directorio");
        return;
    }

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Error al abrir el archivo de salida");
        closedir(dir);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG && strstr(entry->d_name, ".pdf")) {
            char pdf_path[1024];
            snprintf(pdf_path, sizeof(pdf_path), "%s/%s", addressPointer, entry->d_name);
            search_phrase_in_pdf(pdf_path, phrasePointer, output_file);
        }
    }

    fclose(output_file);
    closedir(dir);
}

int algoritmoTrejos(char * phrasePointer, char * addressPointer) {
    const char *output_filename = "Final.txt";
    // Procesar el directorio y buscar la frase en los archivos PDF
    process_directory(phrasePointer, addressPointer, output_filename);
    return 0;
}