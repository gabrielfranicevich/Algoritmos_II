#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

//  tupla para guardar un valor del diccionario
typedef struct s_tuple{
    key_t key;
    value_t value;
} tuple;


static bool invrep(dict_t d) {
    dict_t rgt = d == NULL ? NULL : d->right;
    dict_t lft = d == NULL ? NULL : d->left;

    //  si tiene algún hijo
    if(d != NULL && (rgt != NULL || lft != NULL)){
        //  si tiene un hijo a la izquierda
        if(lft != NULL){
            //  si están mal ordenados
            if(key_less(d->key, lft->key)){
                return false;
            }
        }
        //  si tiene un hijo a la derecha
        if(rgt != NULL){
            //  si están mal ordenados
            if(key_less(rgt->key, d->key)){
                return false;
            }
        }
        //  si están bien ordenados se llama invrep para los hijos
        return invrep(lft) && invrep(rgt);
    }
    //  caso base de para todo es true
    return true;
}

//  declara un nodo en el diccionario
static dict_t node_declare(key_t key, value_t value){
    dict_t dict = NULL;

    //  se inicializa
    dict = malloc(sizeof(struct _node_t));
    dict->left = NULL;
    dict->right = NULL;
    dict->key = key;
    dict->value = value;

    return dict;
}

dict_t dict_empty(void) {
    dict_t dict = NULL;
    assert(invrep(dict));
    return dict;
}

//  cambia la definición de una palabra
static dict_t dict_change_def(dict_t * dict_ptr, key_t word, value_t def){
    dict_t dict = *dict_ptr;
    
    //  si las palabras son iguales
    if(key_eq(word, dict->key)){
        //  se destruyen strings 
        dict->key = key_destroy(dict->key);     //  capaz podria destruirse ´word´
        dict->value = value_destroy(dict->value);

        //  se cambian los valores del diccionario
        dict->key = word;
        dict->value = def;
    
    //  si la palabra es menor a la actual
    }else if(key_less(word, dict->key)){
        //  se agrega a la izquierda
        dict->left = dict_change_def(&(dict->left), word, def);
    
    //  cc (si la palabra es mayor a la actual)
    } else{
        //  se agrega a la derecha
        dict->right = dict_change_def(&(dict->right), word, def);
    }
    return dict;    
}

//  añade un nodo con un nuevo key - value
static dict_t dict_add_not_exist(dict_t * dict_ptr, key_t word, value_t def){
    dict_t dict = *dict_ptr;

    //  si el diccionario es nulo
    if(dict == NULL){
        //  se inicializa el diccionario
        return node_declare(word, def);    
    }

    //  si la palabra es menor a la actual
    if(key_less(word, dict->key)){
        //  se agrega a la izquierda
        dict->left = dict_add_not_exist(&(dict->left), word, def);
    
    //  si la palabra es mayor a la actual
    }else{
        //  se agrega a la derecha
        dict->right = dict_add_not_exist(&(dict->right), word, def);
    }
    
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict) && word != NULL && def != NULL );

    //  si la palabra existe
    if(dict_exists(dict, word)){
        //  se cambia la definición
        dict = dict_change_def(&dict, word, def);
    
    //  si la palabra no existe
    }else{
        //  se genera una nueva palabra
        dict = dict_add_not_exist(&dict, word, def);
    }
    
    assert(invrep(dict));
    return dict;
}

static value_t search_rec(dict_t * dict_ptr, key_t word){
    dict_t dict = *dict_ptr;
    value_t def = NULL;

    //  si las palabras son iguales
    if(key_eq(word, dict->key)){
        //  se guarda la definición
        def = dict->value;

    //  si la palabra buscada es menor
    }else if(key_less(word, dict->key)){
        //  se busca a la izquierda
        def = search_rec(&(dict->left), word);
    
    //  cc (la palabra buscada es mayor)
    }else{
        //  se busca a la derecha
        def = search_rec(&(dict->right), word);
    }
    return def;
}

value_t dict_search(dict_t dict, key_t word) {
    assert(invrep(dict));
    
    value_t def = NULL;
    if(dict_exists(dict, word)) def = search_rec(&dict, word);
    
    return def;
}

static bool dict_exists_rec(dict_t * dict_ptr, key_t word){
    dict_t dict = *dict_ptr;
    //  si el diccionario no es nulo
    if(dict != NULL){
        //  si la palabra actual es igual a la buscada
        if(key_eq(word, dict->key)){
            //  existe
            return true;
        
        //  si la palabra actual es mayor a la buscada
        }else if(key_less(word, dict->key)){
            //  se busca a la izquierda
            return dict_exists_rec(&(dict->left), word);
        
        //  cc (si la palabra actual es menor a la buscada)
        } else{
            //  se busca a la derecha
            return dict_exists_rec(&(dict->right), word);
        }
    
    //  si el diccionario es nulo
    } else{
        //  no puede existir
        return false;
    }
}

bool dict_exists(dict_t dict, key_t word) {
    assert(invrep(dict));
    
    if(dict != NULL){
        return dict_exists_rec(&dict, word);
    }

    return false;
}

//  podria hacerse más simple
static unsigned int length_rec(dict_t * dict_ptr){
    dict_t dict = *dict_ptr;
    unsigned int length = 0u;
    if (dict != NULL){
        //  se cuenta el nodo, se cuentan los nodos izq, se cuentan los nodos derechos
        length++;
        length += length_rec(&(dict->left));
        length += length_rec(&(dict->right));
    }
    return length;
}

unsigned int dict_length(dict_t dict) {
    assert(invrep(dict));
    
    unsigned int length = 0u;
    if (dict != NULL){
        length = length_rec(&dict);    
    }
    
    assert(invrep(dict) && (dict == NULL || length > 0));
    return length;
}

//  busca el menor key-value en un diccionario
static tuple dict_min(dict_t dict){
    while (dict->left != NULL){
        dict = dict->left;
    }
    tuple min;
    min.key = dict->key;
    min.value = dict->value;
    return min;
}

//  se podría usar una función auxiliar para liberar un nodo o que reemplace sus valores
static dict_t remove_rec(dict_t * dict_ptr, key_t word){
    dict_t dict = *dict_ptr;
    dict_t lft = dict != NULL ?dict->left : NULL;
    dict_t rgt = dict != NULL ?dict->right: NULL;

    //  la palabra es menor a la raiz
    if (key_less(word, dict->key)){
        //  se borra de la izquierda
        dict -> left = remove_rec(&lft, word);

    //  la palabra es mayor a la raiz
    }else if(key_less(dict->key, word)){
        //  se borra de la derecha
        dict -> right = remove_rec(&rgt, word);
    
    //  word es el elemento a borrar
    }else{
        //  si no hay elemento a la izquierda
        if(lft == NULL){

            //  se libera la memoria
            dict->key = key_destroy(dict->key);
            dict->value = value_destroy(dict->value);
            free(dict);

            //  se sube el elemento a la derecha
            dict = rgt;

        //  si no hay elemento a la derecha
        } else if(rgt == NULL){
            //  se libera la memoria
            dict->key = key_destroy(dict->key);
            dict->value = value_destroy(dict->value);
            free(dict);

            //  se sube el elemento a la izquierda
            dict = lft;

        //  si hay elementos a derecha e izquierda
        } else{
            //  se reeplaza el nodo con el elemento mínimo de la derecha
            tuple rgt_min = dict_min(rgt);
            dict -> value = value_destroy(dict->value);
            dict -> key = key_destroy(dict->key);
            dict -> key = rgt_min.key;
            dict -> value = rgt_min.value;

            //  se elimina el elemento que se usó previamente
            dict -> right = remove_rec(&(dict -> right), rgt_min.key);  
        
        }
    }
    return dict;
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));

    //  se elimina solo si existe
    if(dict_exists(dict, word)){
        dict = remove_rec(&dict, word);
    }
    
    assert(invrep(dict) && !dict_exists(dict, word));
    return dict;
}

static dict_t remove_all_rec(dict_t * dict_ptr){
    dict_t dict = *dict_ptr;
    
    if (dict!= NULL){
        //  se borran elementos siguientes
        remove_all_rec(&dict->left);
        remove_all_rec(&dict->right);
    
        //  se libera la memoria
        dict->key = key_destroy(dict->key);
        dict->value = value_destroy(dict->value);
        free(dict);
        dict_ptr = NULL;
    }
    
    return NULL;
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    
    dict = remove_all_rec(&dict);
    dict = NULL;

    return dict;
}

//  imprime de menor a mayor, IN-ORDER
static void dump_rec(dict_t * dict_ptr, FILE * file){
    dict_t dict = *dict_ptr;
    //  recursivo hasta NULL
    if(dict != NULL){
        //  imprime los menores
        dump_rec(&(dict->left), file);

        //  se imprime a sí mismo
        key_dump(dict->key, file);
        fprintf(file, ": ");
        value_dump(dict->value, file);
        fprintf(stdout, "\n");

        //  imprime los mayores
        dump_rec(&(dict->right), file);
    }
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    
    if (dict != NULL){
        dump_rec(&dict, file);
    }
    
}

dict_t dict_destroy(dict_t dict) {
    assert(invrep(dict));
    
    dict = remove_all_rec(&dict);
    //  no sé por qué este free, pero está bien
    free(dict);
    dict = NULL;

    return dict;
}