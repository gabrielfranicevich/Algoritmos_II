#include <stdbool.h>

//  acá se escriben los prototípos de las funciones
//  esto es: qué valores toman y qué devuelven

/**
 * Transporta un arreglo de filepath a array
 * @param array al terminar la ejecución contendra el array del filepath
 * @param max_size el tamaño máximo del array
 * @param filepath la direccón del archivo que contiene el array
 * @returns size del array recibido
 */
unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath);

/**
 * Imprime un array dado su tamaño
 * @param a el array a imprimir
 * @param length el tamaño
 */
void array_dump(int a[], unsigned int length);

/**
 * Indica si el arreglo pasado por parámetros está ordenado o no
 * @param a el array
 * @param length el tamaño del array
 * @returns true si el arreglo está ordenado,
 * @returns false en caso contrario
 */
bool array_is_sorted(int a[], unsigned int length);