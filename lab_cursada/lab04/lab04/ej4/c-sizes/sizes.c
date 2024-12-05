#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "data.h"

void
print_data(data_t d) {
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

int main(void) {

    data_t messi = {"Leo Messi", 36, 169};
    print_data(messi);

    printf("name-size  : %lu bytes\n"
           "age-size   : %lu bytes\n"
           "height-size: %lu bytes\n"
           "data_t-size: %lu bytes\n", 
           sizeof(messi.name),
           sizeof(messi.age),
           sizeof(messi.height),
           sizeof(messi));

    printf(
        "name-direction  : %p\n"
        "age-direction   : %p\n"
        "heigh-direction : %p\n"
        "data_t-direction: %p\n",
        (void *) &messi.name,
        (void *) &messi.age,
        (void *) &messi.height,
        (void *) &messi
    );
    printf(
        "name-index  : %lu\n"
        "age-index   : %lu\n"
        "height-index: %lu\n"
        "data_t-index: %lu\n",
        (uintptr_t) &messi.name,
        (uintptr_t) &messi.age,
        (uintptr_t) &messi.height,
        (uintptr_t) &messi
    );
    return EXIT_SUCCESS;
}

