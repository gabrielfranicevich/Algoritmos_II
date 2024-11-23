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

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool invrep(abb tree) {
    bool b = true;
    if(tree == NULL || (tree->left == NULL && tree->right == NULL)) b = b && true;
    else if((tree->right == NULL && tree->elem < tree->left->elem) || 
            (tree->left == NULL && tree->right->elem < tree->elem)) b = false;        // checks the order
    else b = invrep(tree->left) && invrep(tree->right);
    return b;
}

abb abb_empty(void) {
    abb tree;
    tree=NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (abb_is_empty(tree)){
        tree = malloc(sizeof(struct _s_abb));
        tree->elem = e;
        tree->left=abb_empty();
        tree->right=abb_empty();
    }
    else {
        abb_elem root=tree->elem;
        if(elem_less(root,e)){
            tree->right=abb_add(tree->right,e);
        }else if(elem_less(e,root)){
            tree->left=abb_add(tree->left,e);
        }else{
            printf("Reapeted elements are not allowed.\n");
            assert(!elem_eq(root,e));
        }
    }

    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    bool is_empty=false;
    assert(invrep(tree));
    is_empty = tree == NULL;
    return is_empty;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));
    if(tree==NULL){
        exists=false;
    }else if(e==tree->elem){
        exists=true;
    }else if(e>tree->elem){
        exists=abb_exists(tree->right,e);
    }else{
        exists=abb_exists(tree->left,e);
    }
    assert(abb_length(tree)!=0 || !exists);
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    if(tree != NULL){
        length = 1 + abb_length(tree->left) + abb_length(tree->right);
    }
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (!abb_is_empty(tree)){
        abb_elem root=tree->elem;
        if (root < e){
            tree->right=abb_remove(tree->right, e);
        }else if (root > e){
            tree->left=abb_remove(tree->left, e);  
        }else if ((e == root) && abb_is_empty(tree->left)){
            abb right=tree->right;
            free(tree);
            tree=right;
        }else{ 
            abb_elem min_right = abb_min(tree->right);
            tree->elem = min_right;
            tree->right = abb_remove(tree->right, min_right);
        }
    }
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));

    root=tree->elem;

    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    
    abb aux=tree;
    while(aux->right!=NULL){
        aux=aux->right;
    }
    max_e=aux->elem;

    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    abb aux=tree;
    while(aux->left!=NULL){
        aux=aux->left;
    }
    min_e=aux->elem;
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree, abb_ordtype ord) {
    assert(invrep(tree) && (ord==ABB_IN_ORDER  || 
                            ord==ABB_PRE_ORDER ||
                            ord==ABB_POST_ORDER));
    if (tree != NULL) {
        if (ord == ABB_IN_ORDER) {
            abb_dump(tree->left, ord);
            printf("%d ", tree->elem);
            abb_dump(tree->right, ord);
        } else if (ord == ABB_PRE_ORDER) {
            printf("%d ", tree->elem);
            abb_dump(tree->left, ord);
            abb_dump(tree->right, ord);
        } else if (ord == ABB_POST_ORDER) {
            abb_dump(tree->left, ord);
            abb_dump(tree->right, ord);
            printf("%d ", tree->elem);
        }
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if(tree!=NULL){

        tree->left=abb_destroy(tree->left);
        tree->right=abb_destroy(tree->right);

        free(tree);
        tree=NULL;
    }
    assert(tree == NULL);
    return tree;
}

