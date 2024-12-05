#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strfuncs.h"

#define MAX_LENGTH 57

#define SIZEOF_ARRAY(s) (sizeof(s) / sizeof(*s))

bool read_input(char input[]){
    char aux[MAX_LENGTH + 3];
    memset(aux, 0, sizeof(aux));

    if (fgets(aux, MAX_LENGTH + 3, stdin) == NULL) {
        fprintf(stderr, " error al leer la entrada\n");
        return false;
    }
    size_t len = string_length(aux);
    if (len > 0 && aux[len-1] == '\n') {
        aux[len-1] = '\0';
    }

    if (len >= MAX_LENGTH + 1) {
        fprintf(stdout, " string demasiado larga\n");
        return false;
    }
    
    string_copy(input, aux);
    return true;
}
int main(void) {
    char user_input[MAX_LENGTH];
    char ignore_chars[] = {' ', '?', '!', ',', '-', '.', '\n'};
    char *filtered = NULL;

    printf("Ingrese un texto (no más de %d símbolos) para verificar palíndromo: \n", MAX_LENGTH);  
    if (!read_input(user_input)) {
        return EXIT_FAILURE;
    }

    filtered = string_filter(user_input, ignore_chars[0]);
    char * aux = NULL;
    for (unsigned int i=0; i < SIZEOF_ARRAY(ignore_chars); i++) {
        aux = string_filter(filtered, ignore_chars[i]);
        free(filtered);
        filtered = aux;
    }

    printf("El texto:\n\n"
            "\"%s\" \n\n"
            "%s un palíndromo.\n\n", user_input, string_is_symmetric(filtered) ? "Es": "NO es");
    
    free(filtered);
    return EXIT_SUCCESS;
}

