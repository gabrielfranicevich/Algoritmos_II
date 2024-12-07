#include <stdlib.h>   /* malloc(), free(), NULL  */
#include <stdbool.h>  /* Definition of bool      */
#include <stdio.h>    /* printf()                */
#include <assert.h>   /* assert()                */

#include "plist.h"      /* Iterface */

struct s_node {
    t_elem elem;
    struct s_node *next;
};

typedef struct s_node * node_t;

struct s_plist {
    node_t piv;
    node_t left;
    node_t leftmost;
    unsigned int size;
};

static void * alloc_help(size_t size, const char * message){
    void *ptr = malloc(size);
    if(ptr == NULL){
        fprintf(stderr, "error alloc: %s", message);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

/* Creates a single node in dynamic memory containing the element <e>. */
static node_t create_node(t_elem e) {
    node_t new = NULL;

    new = alloc_help(sizeof(struct s_node), "new node");
    new->elem = e;
    new->next = NULL;

    return new;
}

/* Destroys a single node */
static node_t destroy_node(node_t node) {
    node->next = NULL;
    free(node);
    node = NULL;
    return node;    
}

/* Representation invariant */
static bool invrep(plist l) {
    return l != NULL;
}

/* CONSTRUCTORS */

plist plist_create(t_elem pivot) {
    plist list = NULL;

    list = alloc_help(sizeof(struct s_plist), "new plist");
    list->left = NULL;
    list->piv = create_node(pivot);
    list->leftmost = list->piv;
    list->size = 1;

    return list;
}

static plist add_right(plist *l, t_elem e){
    plist list = *l;

    node_t new = create_node(e);
    new->next = list->piv->next;
    list->piv->next = new;

    return list;
}

static plist add_left(plist *l, t_elem e){
    plist list = *l;

    node_t new = create_node(e);
    new->next = list->piv;

    if (list->left == NULL){
        list->left = new;
        list->leftmost = new;
    } else{
        list->left->next = new;
        list->left = new;
    }

    return list;
}

plist plist_add(plist l, t_elem e) {

    if (t_elem_greater(e, l->piv->elem)){
        l = add_right(&l, e);
    }else{
        l = add_left(&l, e);
    }
    l->size++;
    return l;
}

/* OPERATIONS   */
unsigned int plist_length(plist l) {
    return l->size;
}

bool plist_is_empty(plist l) {
    return plist_length(l) == 1;
}

t_elem plist_get_pivot(plist l) {
    return l->piv->elem;
}

plist plist_delete_prev(plist l) {

    if(l->leftmost == l->piv || l->left == NULL){
        return l;
    }

    node_t traveler = l->leftmost;

    while(traveler->next != l->left && traveler != l->left){
        traveler = traveler->next;
    }

    if(traveler->next == l->piv){
        l->leftmost = l->piv;
        traveler = destroy_node(traveler);
        l->size--;
        return l;
    }

    traveler->next = destroy_node(traveler->next);
    traveler->next = l->piv;
    l->left = traveler;

    l->size--;
    return l;
}

plist plist_delete_next(plist l) {
    if (l->piv->next == NULL){
        return l;
    }
    node_t killme = l->piv->next;
    l->piv->next = l->piv->next->next; 
    killme = destroy_node(killme);

    l->size--;
    return l;
}

unsigned int plist_count(plist l, t_elem e) {
    node_t traveler = l->leftmost;
    unsigned int count = 0;
    while(traveler != NULL){
        if (traveler->elem == e){
            count++;
        }
        traveler = traveler->next;
    }
    return count;
}

t_elem * plist_to_array(plist l) {
    t_elem *array = alloc_help(sizeof(t_elem) * plist_length(l), "array");

    node_t traveler = l->leftmost;
    unsigned int i = 0;
    while(traveler != NULL){
        array[i] = traveler->elem;
        traveler = traveler->next;
        i++;
    }
    return array;
}

void plist_dump(plist l) {
    assert(invrep(l));
    if (plist_is_empty(l)) {
        printf("[]");
    } else {
        t_elem *elems = plist_to_array(l);
        printf("[ ");
        t_elem_dump(elems[0]);
        for (unsigned int i=1; i < plist_length(l); i++) {
            printf(", ");
            t_elem_dump(elems[i]);
        }
        printf(" ]");
        free(elems);
    }
}

plist plist_destroy(plist l) {
    node_t traveler = l->leftmost, killme;

    while (traveler != NULL){
        killme = traveler;
        traveler = traveler->next;
        killme = destroy_node(killme);
    }
    free(l);
    return l;
}