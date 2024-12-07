#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "matchTimeline.h"

/* ============================================================================
STRUCTS
============================================================================ */

struct s_node {
    team team;
    event e;
    time t;
    playerNumber pn;
    struct s_node *next;
};

typedef struct s_score{
    unsigned int Home;
    unsigned int Away;
} score;

struct s_matchTimeline {
    struct s_node *head;    //  getting some head
    struct s_node *last;
    unsigned int size;
    score sc;
};

/* ============================================================================
INVERP & VALIDATION
============================================================================ */

static bool invrep(matchTimeline mt){
    struct s_node * traveler = mt->head;
    while(traveler != NULL){
        if(traveler->t > 90){            
            return false;
        }
        traveler = traveler->next;
    }
    return mt != NULL;
}

bool matchTimeline_is_time_and_score_valid(matchTimeline mt){
    struct s_node * traveler = mt->head;
    unsigned int Home_c = 0, Away_c = 0;
    while(traveler != NULL){
        if(traveler->e == Goal){            
            if (traveler->team == Home){
                Home_c++;
            } else {
                Away_c++;
            }
        }
        if (traveler->next != NULL && traveler->t > traveler->next->t) return false;
        traveler = traveler->next;
    }
    return (mt->sc.Away == Away_c && mt->sc.Home == Home_c);
}

/* ============================================================================
CONSTRUCTOR
============================================================================ */

static void * alloc_help(size_t size, const char * message){
    void *ptr = malloc(size);
    if(ptr == NULL){
        fprintf(stderr, "error alloc: %s", message);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

matchTimeline matchTimeline_empty(void){
    matchTimeline mt = NULL;
    mt = alloc_help(sizeof(struct s_matchTimeline), "empty matchTimeline");
    mt->head = NULL;
    mt->size = 0;
    mt->sc.Away = 0;
    mt->sc.Home = 0;
    mt->last = NULL;

    assert(invrep(mt));
    return mt;
}

/* ============================================================================
INSERTION
============================================================================ */

static struct s_node *create_node(team team, event e, time t, playerNumber pn) {

    struct s_node *new_node = NULL;

    new_node = alloc_help(sizeof(struct s_node), "nodo");
    new_node->e = e;
    new_node->next = NULL;
    new_node->pn = pn;
    new_node->t = t;
    new_node->team = team;

    return new_node;
}

/* ============================================================================
GOAL
============================================================================ */

static matchTimeline matchTimeline_event(matchTimeline * mt_ptr, team team, event e ,time t, playerNumber pn){
    matchTimeline mt = *mt_ptr;

    if (t > 90){
        return mt;
    }

    struct s_node* new = create_node(team, e, t, pn);

    if(mt->size == 0){
        mt->head = new;
        mt->last = new;
    } else{
        mt->last->next = new;
        mt->last = new;
    }

    mt->size++;
    return mt;
}

matchTimeline matchTimeline_score_goal(matchTimeline mt, team team, time t, playerNumber pn){
    assert(invrep(mt));
    
    mt = matchTimeline_event(&mt, team, Goal, t, pn);
    if(!(t > 90)){
        if (team == Away){
            mt->sc.Away++;
        } else{
            mt->sc.Home++;
        }
    }

    assert(invrep(mt));
    return mt;
}

/* ============================================================================
THE CARDS
============================================================================ */

matchTimeline matchTimeline_receive_yellowCard(matchTimeline mt, team team, time t, playerNumber pn){
    assert(invrep(mt));

    struct s_node* traveler = mt->head;
    
    while(traveler != NULL){
        if (traveler->e == YellowCard && traveler->pn == pn && traveler->team == team){
            mt = matchTimeline_event(&mt, team, YellowCard, t, pn);
            mt = matchTimeline_event(&mt, team, RedCard, t, pn);
            assert(invrep(mt));
            return mt;
        }
        traveler= traveler->next;
    }
    mt = matchTimeline_event(&mt, team, YellowCard, t, pn);
    assert(invrep(mt));
    return mt;
}

matchTimeline matchTimeline_receive_redCard(matchTimeline mt, team team, time t, playerNumber pn){
    assert(invrep(mt));
    
    mt = matchTimeline_event(&mt, team, RedCard, t, pn);

    assert(invrep(mt));
    return mt;
}

/* ============================================================================
SCORE
============================================================================ */

unsigned int matchTimeline_get_score(matchTimeline mt, team team){
    assert(invrep(mt));
    
    if(team == Away){
        return mt->sc.Away;
    }
    return mt->sc.Home;
}

/* ============================================================================
SIZE
============================================================================ */

unsigned int matchTimeline_size(matchTimeline mt){
    assert(invrep(mt));
    
    return mt->size;
}

/* ============================================================================
PRINT
============================================================================ */

void matchTimeline_print(matchTimeline mt){
    fprintf(
        stdout, "            Home %u -  %u Away \n", 
        matchTimeline_get_score(mt, Home), 
        matchTimeline_get_score(mt, Away)
    );

    struct s_node *aux = mt->head;
    while (aux != NULL) {
        unsigned int t = aux->t;
        char *e;
        switch (aux->e)
        {
        case Goal:
            e = "    Goal   ";
            break;
        case YellowCard:
            e = "Yellow Card";
            break;
        case RedCard:
            e = "  Red Card ";
            break;
        }
        unsigned int pn = aux->pn;

        if (aux->team == Home) {
            fprintf(stdout, "%u - %s - %u' \n", pn, e, t);
        }
        else {
            fprintf(stdout, "                   %u' - %s - %u \n", t, e, pn);
        }

        aux = aux->next;
    }
}

/* ============================================================================
ARRAY
============================================================================ */

event *matchTimeline_events_array(matchTimeline mt){
    assert(invrep(mt));
    event *array = NULL;
    
    array = alloc_help(sizeof(event) * matchTimeline_size(mt), "array of events");

    struct s_node * traveler = mt->head;
    unsigned int i = 0;

    while(traveler != NULL){
        array[i] = traveler->e;
        traveler = traveler->next;
        i++;
    }

    return array;
}

/* ============================================================================
DESTRUCTOR!
============================================================================ */

static struct s_node *destroy_node(struct s_node *node){
    node->next = NULL;
    free(node);
    node = NULL;
    return node;
}

matchTimeline matchTimeline_destroy(matchTimeline mt){
    assert(invrep(mt));
    struct s_node *traveler = mt->head, 
    *killme = NULL;

    while(traveler != NULL){
        killme = traveler;
        traveler = traveler->next;
        killme = destroy_node(killme);
    }
    free(mt);
    
    return mt;
}
