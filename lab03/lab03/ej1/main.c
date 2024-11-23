#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

unsigned int 
data_from_file (const char *path, 
                unsigned int indexes[], 
                char letters[], 
                unsigned int max_size) {
    
    unsigned int length = 0;        
    FILE *file = fopen(path, "r");  // abre el archivo en modo lectura

    if(file == NULL){
        printf("archivo no encontrado\n");
        exit(EXIT_FAILURE);
    }                               //devuelve error cuando el archivo no existe

    for (unsigned int i = 0; i < max_size && !feof(file); i++){
        if(fscanf(file, "%u -> *%c*", &indexes[i], &letters[i]) == 2) length++;
    }                               //equipara length al tamaño verdadero
                                    //feof verifica que el archivo no haya llegado al final, 

    for (unsigned int i = 0; i < length; i++){
        if(indexes[i] >= length){
            printf ("El valor del indice %u = %u es mas grande que length\n", 
                    i, indexes[i]);
            exit(EXIT_FAILURE);
        } 
    }                               //devuelve error si algun indice excede el tamaño de length
    fclose(file);
    return length;
}

void sort_letters(unsigned int indexes[], char letters[], char sorted[], unsigned int length) {
    for (unsigned int i = 0; i < length; i++) {
        for (unsigned int j = 0; j < length; j++) {
            if(i == indexes[j]) { 
                sorted[i] = letters[j]; 
            }
        }
    }
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length=0; 

    filepath = parse_filepath(argc, argv);

    length = data_from_file(filepath, indexes, letters, MAX_SIZE);

    sort_letters(indexes, letters, sorted, length);

    dump(sorted, length);

    return EXIT_SUCCESS;
}

