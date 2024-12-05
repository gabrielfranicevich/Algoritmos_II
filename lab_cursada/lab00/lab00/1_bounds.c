#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound (int value, int arr[], unsigned int length)
{
    //  se declaran valores iniciales para los datos
    struct bound_data res;
    res.is_upperbound = true;
    res.is_lowerbound = true;
    res.exists = false;
    
    int i = 0;
    while (i < length)
    {
        //  si existe un número mayor, no es cota superior
        if (value < arr[i]){
            res.is_upperbound = false;
        } 
        //  si existe un número menor, no es cota inferior
        if (value > arr[i]){
            res.is_lowerbound = false;
        }
        //  si hay un valor igual, se encuentra en el arreglo y en la posición de este valor
        if (value == arr[i]){
            res.exists = true;
            res.where = i;
        }
        i = i + 1;
    }
    return res;
}

int main(void) {
    int a[ARRAY_SIZE] = {0, -1, 9, 4};
    int value = 9;
    
    printf("ingresar elementos del array de uno en uno:\n");
    
    //  se piden los elementos del array por consola
    int i = 0;
    while (i < ARRAY_SIZE){
        int input;
        printf("elmento%d\n", i);
        scanf("%d", &input);
        a[i] = input;
        i = i + 1;
    }

    //  se chequea si ´value´ es cota superior, cota inferior, si está en el arreglo y de estar, su posición
    struct bound_data result = check_bound(value, a, ARRAY_SIZE);

    if (result.is_lowerbound && result.exists){
        printf("el valor es minimo y esta en la posicion %d ",result.where);
    }
    if (result.is_lowerbound && (result.exists==0)){
        printf("cota inferior ");
    }
    if (result.is_upperbound && result.exists){
        printf("el valor es maximo y esta en la posicion %d",result.where);
    }
    if (result.is_upperbound && (result.exists==0)){
        printf("cota superior ");
    }

    return EXIT_SUCCESS;
}

