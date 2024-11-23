#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void absolute(int x, int *y) {
    if (x >= 0) {
        *y = x;
    } else {
        *y = -x;
    }
}

int main(void) {
    int a=0, res=0;  
    a = -10; // aca res = 0

    absolute(a, &res); // y aca res vale 10

    printf("%d\n", &res);

    assert(res >= 0 && (res == a || res == -a));
    return EXIT_SUCCESS;
}

/*
*y en absolute nunca se modifica dentro de absolute, solo se modifica 
el valor al que apunta

Programa 1: y se pasa por valor, lo que significa que absolute trabaja con una copia de y 
y cualquier cambio en y dentro de absolute no afecta a res en main.

Programa 2: y se pasa como un puntero (int *y), lo que significa que absolute puede modificar 
directamente el valor de res en main a través del puntero y.
*/