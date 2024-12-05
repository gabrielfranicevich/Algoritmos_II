#include <stdlib.h>
#include <stdio.h>


void absolute(int x, int y) {
    if (x >= 0) {
        y = x;
    } else {
        y = -x;
    }
}

int main(void) {
    int a=0, res=0;
    a = -10;

    absolute(a, res);

    printf("%d\n", &res);

    return EXIT_SUCCESS;
}

/*
Siguiendo la definicion del lenguaje que se le pasa en el teorico, 
el valor que se imprime por pantalla es 10.

En C, el valor que se muestra por pantalla es 0, el valor original de res, 
ya que los valores que le paso a absolute son int

Y las variables x e y tienen el scope limitado a la funcion absolute y res no se modifica.
*/