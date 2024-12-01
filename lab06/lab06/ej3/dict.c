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

static bool invrep(dict_t d) {
    if (d == NULL ) return true;
    dict_t lft = d->left;
    if (lft != NULL){
        if (!key_less(lft->key, d->key)) {
            return false;
        }
        if (!invrep(lft)) return false;
    }
    
    dict_t rgt = d->right;
    if (rgt != NULL){
        if (!key_less(d->key, rgt->key)) {
            return false;
        }
        if (!invrep(rgt)) return false;
    }

    if (lft != NULL && lft->right != d) {
        return false;
    }

    if (rgt != NULL && rgt->left != d) {
        return false;
    }

    return true;
}

//  declara un nodo en el diccionario, según lo que va a estar a su izquierda y su derecha
static dict_t dict_declare( dict_t * left_ptr, dict_t * right_ptr, key_t key, value_t value){
    dict_t dict = NULL;
    dict_t left = left_ptr != NULL? *left_ptr : NULL;
    dict_t right = right_ptr != NULL? *right_ptr : NULL;

    //  se inicializa el diccionario
    dict = malloc(sizeof(struct _node_t));
    dict->left = left;
    dict->right = right;
    dict->key = key;
    dict->value = value;

    //  a la derecha del nodo izquierdo, está el nuevo nodo
    if(left != NULL){
        left->right = dict;
    }

    //  a la izquierda del nodo derecho, está el nuevo nodo
    if(right != NULL){
        right->left = dict;
    }

    return dict;
}

dict_t dict_empty(void) {
    dict_t dict = NULL;
    
    dict = dict_declare(NULL, NULL, NULL, NULL);

    assert(invrep(dict));

    return dict;
}

//  cambia la definición de una palabra
static dict_t dict_add_exist(dict_t * dict_ptr, key_t word, value_t def){
    dict_t dict = *dict_ptr;
    
    //  si las palabras son iguales
    if(key_eq(word, dict->key)){
        //  se cambia la definicion
        dict->value = value_destroy(dict->value);
        dict->value = def;
    
    //  si la palabra es menor a la actual
    }else if(key_less(word, dict->key)){
        //  se agrega a la izquierda
        dict->left = dict_add_exist(&(dict->left), word, def);
    
    //  cc (si la palabra es mayor a la actual)
    } else{
        //  se agrega a la derecha
        dict->right = dict_add_exist(&(dict->right), word, def);
    }
    return dict;    
}

//  añade un nodo con un nuevo key - value
static dict_t dict_add_not_exist(dict_t * dict_ptr, key_t word, value_t def){
    dict_t dict = *dict_ptr;
    
    //  si la palabra es menor a la actual
    if(key_less(word, dict->key)){

        dict_t lft = dict->left;

        //  si no hay nada a la izquierda, se agrega
        if(lft == NULL){
            dict->left = dict_declare(NULL, &dict, word, def);

        //  si la palabra es menor a la de la izquierda
        } else if (key_less(word, lft->key)){
            //  se busca lugar a la izquierda
            dict->left = dict_add_not_exist(&lft, word, def);
        
        //  cc (si la palabra es mayor a la de la izquierda)
        } else{
            //  se agrega en la siguiente posición a la izquierda
            dict->left = dict_declare(&lft, &dict, word, def);               
        }
    
    // cc (si la palabra es mayor a la actual)
    } else{
        
        dict_t rgt = dict->right;

        //  si no hay nada a la derecha, se agrega
        if(dict->right == NULL){
            dict->right = dict_declare(&dict, NULL, word, def);
        
        //  si la palabra es mayor a la de la derecha
        } else if(key_less(dict->right->key, word)){
            //  se busca lugar a la derecha
            dict->right = dict_add_not_exist(&(dict->right), word, def);
        
        //  cc (si la palabra es menor a la de la derecha)
        } else{
            //  se agrega en la siguiente posición a la derecha
            dict->right = dict_declare(&dict, &rgt, word, def);
        }
    }
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict) && word != NULL && def != NULL );

    //  si el diccionario es vacío
    if(dict_length(dict) == 0){
        //  si el diccionario es nulo
        if(dict == NULL){
            //  se inicializa el diccionario
            dict = dict_declare(NULL, NULL, word, def);
        
        //  si el diccionario no es nulo
        }else{
            //  se escriben los valores de la primera palabra
            dict->key = word;
            dict->value = def;
        }

    //  si la palabra existe
    }else if(dict_exists(dict, word)){
        //  se cambia la definición
        dict = dict_add_exist(&dict, word, def);
    
    //  si la palabra no existe
    }else{
        //  se genera una nueva palabra
        dict = dict_add_not_exist(&dict, word, def);
    }
    
    //assert(invrep(dict));
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
    
    //  cc (la palabra buscada es mayors)
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
            return dict_exists(dict->left, word);
        
        //  cc (si la palabra actual es menor a la buscada)
        } else{
            //  se busca a la derecha
            return dict_exists(dict->right, word);
        }
    
    //  si el diccionario es nulo
    } else{
        //  no puede existir
        return false;
    }
}

bool dict_exists(dict_t dict, key_t word) {
    assert(invrep(dict));
    
    
    if(dict_length(dict) != 0){
        return dict_exists_rec(&dict, word);
    }

    return false;
}

//  corregir
unsigned int dict_length(dict_t dict) {
    assert(invrep(dict));
    unsigned int length = 0;
    
    //  si el diccionario no es nulo
    if (dict != NULL) {
        //  me voy todo a la izquierda posible
        while(dict -> left != NULL){
            dict = dict -> left;
        }
        //  cuento todos los de la derecha
        while(dict != NULL){
            if(dict -> key != NULL) length++;
            dict = dict -> right;
        }
    }
    return length;
}

//  uso direcciones para evitar memory leaking
static dict_t remove_rec(dict_t * dict_ptr, key_t word){
    dict_t dict = *dict_ptr;

    //  si las palabras son iguales
    if (key_eq(word, dict->key)){
        //  si no hay nada a izquierda o derecha
        if(dict->right == NULL && dict->left == NULL){
            
            
            //  se libera la memoria
            dict->key = key_destroy(dict->key);
            dict->value = value_destroy(dict->value);
            free(dict);
            
            return NULL;
        
        //  si no hay nada a la izquierda
        } else if(dict -> left == NULL){
            dict_t rgt = dict -> right;
            
            //  se libera la memoria
            dict->key = key_destroy(dict->key);
            dict->value = value_destroy(dict->value);
            free(dict);
            
            //  rgt es el nuevo dict
            return rgt;

        //  si no hay nada a la derecha
        } else if( dict -> right == NULL){
            dict_t lft = dict -> left;
            
            //  se libera la memoria
            dict->key = key_destroy(dict->key);
            dict->value = value_destroy(dict->value);
            free(dict);
            
            //  dict apunta a lft
            return lft;

        //  si hay algo en ambas posiciones
        } else{
            dict_t lft = dict->left, rgt = dict->right;

            //  a la izquierda de rgt está lft
            rgt -> left = lft;
            //  el nodo lft todavía no apunta a right
            lft -> right = rgt;
            
            //  se libera la memoria
            dict->key = key_destroy(dict->key);
            dict->value = value_destroy(dict->value);
            free(dict);
            
            //  dict apunta a lft
            return lft;
        }

    //  si la palabra buscada es menor
    } else if(key_less(word, dict->key)){
        //  se busca a   la izquierda
        dict -> left = remove_rec(&dict->left, word);
    
    //  cc (la palabra buscada es mayor)
    } else{
        //  se busca a la derecha
        dict -> right = remove_rec(&dict->right, word);
    }
    return dict;
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));

    if(dict_exists(dict, word)){
        dict = remove_rec(&dict, word);
    }
    
    assert(invrep(dict) && !dict_exists(dict, word));
    return dict;
}

static dict_t remove_all_rec(dict_t * dict_ptr){
    dict_t dict = *dict_ptr;
    
    remove_all_rec(&dict->left);
    remove_all_rec(&dict->right);
    
    dict->key = key_destroy(dict->key);
    dict->value = value_destroy(dict->value);
    free(dict);
    
    return NULL;
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    
    dict = remove_all_rec(&dict);
    
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    while (dict->left != NULL){
        dict = dict->left;
    }
    while (dict != NULL){
        key_dump(dict->key, file);
        fprintf(file, ": ");
        value_dump(dict->value, file);
        fprintf(file, "\n");
        dict = dict->right;
    }
    
}

dict_t dict_destroy(dict_t dict) {
    assert(invrep(dict));
    
    dict = remove_all_rec(&dict);
    free(dict);
    dict = NULL;

    return dict;
}

