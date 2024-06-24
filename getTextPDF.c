#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <poppler/glib/poppler.h>

// El puntero char va a almacena todo el texto extraido del PDF
char* extract_text_from_pdf(const char *pdf_path, const char *pdf_filename) {
    // Almacenar la ruta completa del archivo PDF
    // Se usa sprintf para fomentar la cadena con la ruta y el nombre del archivo
    char *full_path = (char*)malloc(strlen(pdf_path) + strlen(pdf_filename) + 2);
    sprintf(full_path, "%s/%s", pdf_path, pdf_filename);

// Apertura del docuemnto PDF
GError *error = NULL;
    PopplerDocument *document = poppler_document_new_from_file(full_path, NULL, &error);
    free(full_path);

// mensaje de error
if (!document) {
    fprintf(stderr, "Error al abrir el archivo: %s\n", error->message);
    g_error_free(error);
    return NULL;
}


// Mostrar el numero de paginas del archivo por cualquier cosa si fuera necesario
int num_pages = poppler_document_get_n_pages(document);
    printf("El documento tiene %d páginas.\n", num_pages);

// Calcular el tamano necesario para almacenar el texto de todas las paginas

size_t total_length = 0;
for (int i = 0; i < num_pages; i++) {
    PopplerPage *page = poppler_document_get_page(document, i);
    if (page) {
        char *text = poppler_page_get_text(page);
        if (text) {
            total_length += strlen(text);
            g_free(text);
        }
        g_object_unref(page);
    }
}



// Asignar la memoria para todo el texto
char *all_text = (char*)malloc(total_length + 1);
    all_text[0] = '\0';

// Extraer y concatenar el texto

    for (int i = 0; i < num_pages; i++) {
        PopplerPage *page = poppler_document_get_page(document, i);
        if (page) {
            char *text = poppler_page_get_text(page);
            if (text) {
                strcat(all_text, text);
                g_free(text);
            }
            g_object_unref(page);
        }
    }
// liberar el documento y delvolver el texto
    g_object_unref(document);
    return all_text;
}


/*

Para utilizar, se puede crear otro archivo .h para declarar la funcion, este puede tener una estructura similar a la siguiente:

----------------------------------------------------------------------------------

#ifndef PDF_EXTRACTOR_H
#define PDF_EXTRACTOR_H

char* extract_text_from_pdf(const char *pdf_path, const char *pdf_filename);

#endif // PDF_EXTRACTOR_H

----------------------------------------------------------------------------------

Para implementarlo se puede adotar una estructura de la siguiente manera:


-----------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "pdf_extractor.h"

int main() {
    const char *pdf_path = "/ruta/al/archivo"; // Cambia esto al path correcto
    const char *pdf_filename = "archivo.pdf";  // Cambia esto al nombre del archivo correcto

    char *pdf_text = extract_text_from_pdf(pdf_path, pdf_filename);
    if (pdf_text) {
        printf("Texto extraído:\n%s\n", pdf_text);
        free(pdf_text);
    } else {
        fprintf(stderr, "Error al extraer el texto del PDF.\n");
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------


*/



