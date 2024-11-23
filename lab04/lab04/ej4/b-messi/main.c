#include <stdio.h>
#include <stdlib.h>

#include "data.h"

/*
typedef char name_t [NAME_MAXSIZE]; // name_t es un tipo de arreglos de caracteres

typedef struct _s_data {
    name_t name;
    unsigned int age;
    unsigned int height;
} data_t;
*/

void print_data(data_t d) {
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

void set_name(name_t new_name, data_t *d) {
    unsigned int i = 0;
    // Mientras el caracter en la posicion i no sea el ultiumo,
    // d->name[i] = new_name copia el i-esimo caractyer de d->name en el i-esimo caracter de new_name 
    while(new_name[i] != '\0'){
        // d es u n puntero a una estructura de tipo data_t
        // d->name accede al miembro name de la estructura apuntada por d
        // d->name[i] accede al i-esimo caracterdel array name
        d->name[i] = new_name[i];
        i++;
    }
    d->name[i] = '\0';
}


// El main imprime los datos y define los arreglos con sus datos predefinidos
int main(void) {

    data_t messi = {"Leo Messi", 36, 169};
    print_data(messi);
    name_t messi_full_name = "Lionel Messi";
    set_name(messi_full_name, &messi);
    print_data(messi);

    return EXIT_SUCCESS;
}

