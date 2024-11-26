#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>

/* list as a pointer to structs to guarantee encapsulation */
typedef struct node * list;
typedef int list_elem;
typedef void proc;
typedef unsigned int nat;

/* Constructors */

//  Crea una lista vacía
list empty_list(void);

//  añade un elemento a la izquierda de la lista
list addl(list l, list_elem e);

/* Destroy */

//  libera memoria utilizada
list destroy_list(list l);

/* Operations */

//  devuelve true si la lista es vacía, false en cc
bool is_list_empty(list);

/**
 * @brief - Devuelve el primer elemento de la lista ´l´
 * 
 * PRE:
 * 
 * - !is_list_empty(l)
 */
list_elem head(list l);

/**
 * @brief - Elimina el primer elemento de la lista ´l´
 * 
 * PRE:
 * 
 * - !is_list_empty(l)
 */
list tail(list l);

//  agrega el elemento ´e´ al final de la lista ´l´
list addr(list l, list_elem e);

//   Devuelve la cantidad de elementos de la lista ´l´
nat list_length(list l);

//  Agrega al final de ´l1´ todos los elementos de ´l2´ en el mismo orden
list list_concat(list l1, list l2);

/**
 * @brief - Devuelve el ´n-ésimo´ elemento de la lista ´l´
 * 
 * PRE:
 * 
 * - length(l) > n
 */
list_elem list_index(list l, nat n);

//  Deja en ´l´ sólo los primeros ´n´ elementos, eliminando el resto
list take(list l, nat n);

//  Elimina los primeros ´n´ elementos de ´l´
list drop(list l, nat n);

//  Copia todos los elementos de ´l1´ en la nueva lista ´l2´
list list_copy(list l1);

#endif