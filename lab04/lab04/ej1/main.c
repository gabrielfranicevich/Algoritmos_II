/*
  @file main.c
  @brief Main program function implementation
*/
#include <stdio.h>
#include <stdlib.h>

/** @brief structure which represent a person */
typedef struct _person {
    int age; 
    char name_initial;
} person_t;

/* La estructura person_t toma dos parametros, la edad y la inicial del nombre */

/**
 * @brief Main program function
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(void) {

    int x = 1; // x toma el valor entero 1
    person_t m = {90, 'M'}; // person_t toma el valor 90 en age y M como name_initial
    int a[] = {0, 1, 2, 3};

    int *p = NULL; // Defino los punteros como NULL, ya que si los defino sin valor, pueden tomar cualquier
    char *q = NULL;
    

    p = &x; // esta linea le asigna a p la direccion de memoria donde se encuentra x
            // p es un puntero a entero, por lo tanto p apunta a x
    *p = 9; // Esta linea le asigna el valor 9 a la direccion de memoria a la que apunta p.
            // Dado que p apunta a x, *p se refiere a x, Por lo tanto esta linea es equivalente a x = 9
    // ahora x vale 9

    p = &m.age; // asigna a p la direccion de memoria del miembro age de la estrucutra m 
                // p es un puntero a un entero, age en la estructura person
    *p = 100;   // Le asigna el valor 100 a la direccion de memoria a la que apunta p
                // dado que p apunta a m.age, *p se refiere a m.age, por lo tanto esto es ifual a m.age = 100;
    // ahora m es igual a {100, 'M'}

    q = &m.name_initial; // asigna a q la direccion de memoria del miembro name_initial de la estructura m de tipo person_t
                         // q es un puntero a char
    *q = 'F'; // le asigno el valor 'F' a la direccion de memoria a la que apunta q
              // dado que q apunta a name_initial, *q se refiere a m.name_initial de la estrucutra m de tipo person_t
    // ahora m es igual a {100, 'F'}

    p = &a[1]; // asigna a p la direccion de memoria del indice 1 del array a, el cual tiene valor a[1] = 1
               // q es un puntero al arreglo, especificamente a la posicion 1
    *p = 42;   // le asigno el valor 42 a p, el cual apunta a a[1]
               // esta linea es igual a decir a[1] = 42;
    // ahora a[1] = {0, 42, 2, 3}

    printf("x = %d\n", x);
    printf("m = (%d, %c)\n", m.age, m.name_initial);
    printf("a[1] = %d\n", a[1]);
    
    /* salida por consola:
        x = 9
        m = {100, 'F'}
        a[1] = 42
    */

    return EXIT_SUCCESS;
}