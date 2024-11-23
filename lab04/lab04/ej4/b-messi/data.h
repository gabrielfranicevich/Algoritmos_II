#ifndef _DATA_H_
#define _DATA_H_

#define NAME_MAXSIZE 30

/* name_t es un tipo de dato, el cual es un arreglo de char */
// Basicamente, name_t es un alias que usamos en vez de escribir char *nombre* [NAME_MAXSIZE]
typedef char name_t [NAME_MAXSIZE];

typedef struct _s_data {
    name_t name;
    unsigned int age;
    unsigned int height;
} data_t;


#endif

