#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

//  a < b
static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool invrep(abb tree) {
    abb lft = tree != NULL ? tree->left : NULL;
    abb rgt = tree != NULL ? tree->right : NULL;

    //  si tree tiene algun hijo
    if(tree != NULL && (lft != NULL || rgt != NULL)) {
        
        //  si left existe
        if (lft != NULL) {
            //  si left está mal ordenado o duplicado
            if (lft->elem >= tree->elem) {
                return false;
            }
        }

        //  si right existe
        if (rgt != NULL) {
            //  si right está mal ordenado o duplicado
            if (rgt->elem <= tree->elem) {
                return false;
            }
        }

        //  si están bien ordenados se llama a invrep para los hijos
        return (invrep(lft) && invrep(rgt));
    }
    //  si el árbol no tiene hijos o es NULL
    return true;
}

abb abb_empty(void) {
    abb tree;

    //  se inicializa en NULL
    tree = NULL;
    
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

//  usando direcciones para que no haya memory leaking
static abb abb_add_rec(abb *tree_ptr, abb_elem e){
    abb tree = *tree_ptr;
    //  si el árbol es vacío
    if (tree == NULL){
        tree = malloc(sizeof(struct _s_abb));
        tree -> elem = e;
        tree -> left = NULL;
        tree -> right = NULL;
    
    //  si el elemento ´e´ es menor al elemento del árbol
    }else if (elem_less(e, tree -> elem)) {
        //  se agrega a la izquierda
        tree -> left = abb_add_rec(&(tree -> left), e);

    //  si el elemento ´e´ es mayor al elemento del árbol
    } else if (elem_less(tree -> elem, e)) {
        //  se agrega a la derecha
        tree -> right = abb_add_rec(&(tree -> right), e);
    }
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    
    //  si el elemento no está en el árbol
    if (!abb_exists(tree, e)){
        //  se agrega, en función auxiliar para evitar invrep y abb_exists en cada iteración
        tree = abb_add_rec(&tree, e);
    }

    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    bool is_empty=false;
    assert(invrep(tree));
    
    //  un árbol vacío es nulo según inicialización
    is_empty = (tree == NULL);
    
    return is_empty;
}

//  usando direcciones para que no haya memory leaking
static bool abb_exists_rec(abb *tree_ptr, abb_elem e){
    abb tree = *tree_ptr;
    
    //  si el árbol es vacío
    if(tree == NULL){
        //  ´e´ no puede existir
        return false;
    
    //  si los elementos son iguales
    } else if (elem_eq(tree -> elem, e)){
        //  ´e´ existe
        return true;
    
    //  si el elemento buscado es mayor
    } else if(elem_less(tree -> elem, e)){
        //  se busca a la derecha
        return abb_exists_rec(&(tree -> right), e);
    
    //  cc (el elemento buscado es menor)
    } else {
        //  se busca a la izquierda
        return abb_exists_rec(&(tree -> left), e);
    }
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists = false;
    assert(invrep(tree));

    //  función auxiliar para evitar invrep en cada iteración
    exists = abb_exists_rec(&tree, e);
    
    assert(abb_length(tree) != 0 || !exists);
    return exists;
}

//  usando direcciones para que no haya memory leaking
static unsigned int abb_length_rec(abb *tree_ptr){
    abb tree = *tree_ptr;
    unsigned int length = 0;

    //  si el árbol no es vacío
    if (tree != NULL) {
        //  se cuenta el nodo
        length++;

        //  si existe un elemento a la izquierda
        if (tree -> left != NULL){
            //  se cuentan todos los subárboles izquierdos
            length += abb_length_rec(&(tree -> left));
        }
        //  si existe un elemento a la derecha
        if (tree -> right != NULL){
            //  se cuentan todos los subárboles derechos
            length += abb_length_rec(&(tree -> right));
        }
        
    }
    return length;
}

unsigned int abb_length(abb tree) {
    unsigned int length = 0;
    assert(invrep(tree));
    
    //  función auxiliar para evitar invrep en cada iteración
    length = abb_length_rec(&tree);
    
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

static abb abb_remove_rec(abb *tree_ptr, abb_elem e){
    abb tree = *tree_ptr;

    abb lft = tree != NULL ? tree->left : NULL;
    abb rgt = tree != NULL ? tree->right : NULL;

    //  el elemento es mayor a la raiz
    if(elem_less(tree -> elem, e)){
        //  asumo que el elemento existe, lo busco a la derecha
        tree -> right = abb_remove_rec(&(tree -> right), e);
    
    //  el elemento es menor a la raiz
    } else if (elem_less(e, tree -> elem)){
        //  asumo que el elemento existe, lo busco a la izquierda
        tree -> left = abb_remove_rec(&(tree -> left), e);
    
    //  si son iguales
    } else{

        //  si no hay elemento a la derecha
        if(rgt == NULL){
            free(tree);
            tree = lft;

        //  si hay elemento a la derecha, pero no a la izquierda
        } else if (lft == NULL){
            free(tree);
            tree = rgt;
        
        //  si hay elementos en sus 2 subárboles
        } else{
            //  se reeplaza el nodo con el elemento mínimo de la derecha
            abb_elem rgt_min = abb_min(rgt);
            tree -> elem = rgt_min;

            //  se este elemento del subárbol derecho
            tree -> right = abb_remove_rec(&(tree -> right), rgt_min);  
        }
    }

    return tree;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    
    if (abb_exists(tree, e)){
        abb_remove_rec(&tree, e);
    }
    
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    
    root = tree -> elem;

    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    
    while (tree -> right != NULL){
        tree = tree -> right;
    }
    max_e = tree -> elem;

    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));

    while (tree -> left != NULL){
        tree = tree -> left;
    }
    min_e = tree -> elem;

    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

static void abb_dump_rec(abb *tree_ptr, abb_ordtype ord) {
    abb tree = *tree_ptr;
    if (tree != NULL) { 
        //  IN: se imprime al medio
        if (ord == ABB_IN_ORDER) {
            abb_dump_rec(&tree->left, ord);
            printf("%d ", tree->elem);
            abb_dump_rec(&tree->right, ord);
        
        //  PRE: se imprime al principio
        } else if (ord == ABB_PRE_ORDER) {
            printf("%d ", tree->elem);
            abb_dump_rec(&tree->left, ord);
            abb_dump_rec(&tree->right, ord);

        //  POST: se imprime al final
        } else if (ord == ABB_POST_ORDER) {
            abb_dump_rec(&tree->left, ord);
            abb_dump_rec(&tree->right, ord);
            printf("%d ", tree->elem);
        }
    }
}

void abb_dump(abb tree, abb_ordtype ord) {
    assert(invrep(tree) && (ord == ABB_IN_ORDER  || 
                            ord == ABB_PRE_ORDER ||
                            ord == ABB_POST_ORDER));

    if(tree != NULL){
        abb_dump_rec(&tree, ord);
    }

}

static abb abb_destroy_rec(abb *tree_ptr){
    abb tree = *tree_ptr;
    if (tree != NULL) {
        abb_destroy_rec(&(tree->left));
        abb_destroy_rec(&(tree->right));
        free(tree);
        tree_ptr = NULL;
    }
    return tree;
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    
    tree = abb_destroy_rec(&tree);
    tree = NULL;

    assert(tree == NULL);
    return tree;
}

