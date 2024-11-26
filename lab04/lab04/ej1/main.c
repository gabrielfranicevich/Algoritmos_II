/**
 * @file main.c
 * @brief Main program function implementation
 */
#include <stdio.h>
#include <stdlib.h>

/** La estructura person_t toma dos parametros, la edad y la inicial del nombre */
typedef struct _person {
    int age; 
    char name_initial;
} person_t;

int main(void) {

    int x = 1;
    person_t m = {90, 'M'}; //  person_t toma el valor 90 en age y M como name_initial
    int a[] = {0, 1, 2, 3};

    int *p = NULL; char *q = NULL;
    
    p = &x; //  esta linea le asigna a ´p´ la direccion de memoria donde se encuentra ´x´
            //  ahora ´p´ apunta a ´x´

    *p = 9; //  esta linea le asigna el valor 9 a la direccion de memoria a la que apunta ´p´.
            //  dado que ´p´ apunta a ´x´, ´*p´ se refiere a ´x´
            //  esta linea es equivalente a ´x = 9´
            //  ahora ´x´ vale 9

    p = &m.age; //  asigna a ´p´ la direccion de memoria del atributo ´age´ de la estrucutra ´m´ 
                //  ahora ´p´ apunta a ´m.age´, un entero en la estructura person

    *p = 100;   //  le asigna el valor 100 a la direccion de memoria a la que apunta ´p´
                //  ´*p´ se refiere a ´m.age´
                //  esta linea es equivalente a ´m.age = 100;´
                //  ahora ´m´ es igual a {100, 'M'}

    q = &m.name_initial;    //  asigna ´q´ la direccion de memoria del atributo ´name_initial´ 
                            //  de la estructura ´m´
                            
    *q = 'F';   //  le asigno el valor 'F' a la direccion de memoria a la que apunta ´q´
                //  ´*q´ se refiere a ´m.name_initial´ de la estrucutra ´m´
                //  ahora ´m´ es igual a {100, 'F'}

    p = &a[1];  //  asigna a ´p´ la direccion de memoria del indice 1 del array a
                //  ´q´ a la posicion 1 del arreglo

    *p = 42;    //  le asigno el valor 42 a ´p´
                //  esta linea es igual a decir ´a[1] = 42;´
                //  ahora ´a[1]´ = {0, 42, 2, 3}

    printf("x = %d\n", x);
    printf("m = (%d, %c)\n", m.age, m.name_initial);
    printf("a[1] = %d\n", a[1]);

    return EXIT_SUCCESS;
}