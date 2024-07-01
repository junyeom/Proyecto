#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <poppler/glib/poppler.h>
// guardar nombre del PDF y las paginas donde se encuentra
typedef struct {
    char *filename;
    int *pages;
    int num_pages;
} SearchResult;
// para guardar lista de resultados 
typedef struct {
    SearchResult *results;
    int size;
    int capacity;
} SearchResultList;

// iniciar lista con capacidad de 10 para no hacerla muy grande
void init_search_result_list(SearchResultList *list) {
    list->size = 0;
    list->capacity = 10;
    list->results = (SearchResult *)malloc(list->capacity * sizeof(SearchResult));
}

// Si hay un nuevo resultado lo agrega a la lista
void add_search_result(SearchResultList *list, const char *filename, int *pages, int num_pages) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->results = (SearchResult *)realloc(list->results, list->capacity * sizeof(SearchResult));
    }

    list->results[list->size].filename = strdup(filename);
    list->results[list->size].pages = (int *)malloc(num_pages * sizeof(int));
    memcpy(list->results[list->size].pages, pages, num_pages * sizeof(int));
    list->results[list->size].num_pages = num_pages;
    list->size++;
}

// Liberar memoria
void free_search_result_list(SearchResultList *list) {
    for (int i = 0; i < list->size; i++) {
        free(list->results[i].filename);
        free(list->results[i].pages);
    }
    free(list->results);
}

// Función para extraer el texto del PDF
char* extract_text_from_pdf(const char *pdf_path) {
    GError *error = NULL;
    PopplerDocument *document = poppler_document_new_from_file(pdf_path, NULL, &error);
    if (!document) {
        fprintf(stderr, "Error al abrir el archivo: %s\n", error->message);
        g_error_free(error);
        return NULL;
    }

    int num_pages = poppler_document_get_n_pages(document);
    printf("El documento tiene %d páginas.\n", num_pages);

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

    char *all_text = (char*)malloc(total_length + 1);
    all_text[0] = '\0';

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

    g_object_unref(document);
    return all_text;
}

// guardar el texto en un archivo
void save_text_to_file(const char *filename, const char *text) {
    FILE *file = fopen(filename, "w");
    if (file) {
        fprintf(file, "%s", text);
        fclose(file);
    } else {
        fprintf(stderr, "Error al abrir el archivo para escribir: %s\n", filename);
    }
}

// Función para buscar una frase en el archivo de texto y devolver las páginas en las que aparece
void search_phrase_in_text(const char *filename, const char *phrase, SearchResultList *result_list) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error al abrir el archivo para leer: %s\n", filename);
        return;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int page = 1;
    int found = 0;
    int *pages = (int *)malloc(10 * sizeof(int));
    int num_pages = 0;
    int capacity = 10;

    while ((read = getline(&line, &len, file)) != -1) {
        if (strstr(line, phrase) != NULL) {
            if (num_pages >= capacity) {
                capacity *= 2;
                pages = (int *)realloc(pages, capacity * sizeof(int));
            }
            pages[num_pages++] = page;
            found = 1;
        }
        if (strstr(line, "\f") != NULL) {
            page++;
        }
    }

    if (found) {
        add_search_result(result_list, filename, pages, num_pages);
    }

    free(pages);
    free(line);
    fclose(file);
}

// Función para procesar todos los archivos PDF en un directorio
void process_pdfs_in_directory(const char *dir_path, const char *phrase, SearchResultList *result_list) {
    DIR *dir = opendir(dir_path);
    if (!dir) {
        fprintf(stderr, "Error al abrir el directorio: %s\n", dir_path);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            // Verificar si el archivo tiene la extensión .pdf
            if (strstr(entry->d_name, ".pdf")) {
                char pdf_path[1024];
                snprintf(pdf_path, sizeof(pdf_path), "%s/%s", dir_path, entry->d_name);

                char *pdf_text = extract_text_from_pdf(pdf_path);
                if (pdf_text) {
                    char output_filename[1024];
                    snprintf(output_filename, sizeof(output_filename), "%s.txt", entry->d_name);
                    save_text_to_file(output_filename, pdf_text);
                    free(pdf_text);
                    printf("Texto extraído y guardado en %s\n", output_filename);

                    // Buscar la frase en el archivo de texto
                    search_phrase_in_text(output_filename, phrase, result_list);
                } else {
                    fprintf(stderr, "Error al extraer el texto del PDF: %s\n", pdf_path);
                }
            }
        }
    }

    closedir(dir);
}

int main() {
    const char *dir_path = //poner el path con algo
    const char *phrase = //poner la frase con algo 

    SearchResultList result_list;
    init_search_result_list(&result_list);

    process_pdfs_in_directory(dir_path, phrase, &result_list);

    // para imprimir resultados
    for (int i = 0; i < result_list.size; i++) {
        printf("Archivo: %s\n", result_list.results[i].filename);
        printf("Páginas: ");
        for (int j = 0; j < result_list.results[i].num_pages; j++) {
            printf("%d ", result_list.results[i].pages[j]);
        }
        printf("\n");
    }

    free_search_result_list(&result_list);

    return 0;
}