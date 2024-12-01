#ifndef DICT_H
#define DICT_H

#include <stdio.h>
#include <stdbool.h>
#include "key_value.h"

/**
 * Note: The definition of the structure should be in [dict.c], not here.
 */
typedef struct _node_t *dict_t;

/** Creates an empty dictionary
 *
 * PRE: {true}
 *   dict = dict_empty();
 * POS: {dict --> dict_t /\ dict_length(dict) == 0}
 */
dict_t dict_empty(void);

/** Adds a [word] and its definition [def] in the dictionary.
 * If [word] is already in the dictionary, its definition is replaced by [def].
 *
 * PRE: {dict --> dict_t /\ word --> key_t /\ def --> value_t}
 *  dict = dict_add(dict, word, def);
 * POS: {dict --> dict_t /\ key_eq(def, dict_search(dict, word))}
 */
dict_t dict_add(dict_t dict, key_t word, value_t def);

/** Returns the definition of the given [word], or NULL if [word] is not in
 * the dictionary.
 *
 * Note: Returns a reference to the value_t owned by the dictionary (not a copy).
 *
 * PRE: {dict --> dict_t /\ word --> key_t}
 *   def = dict_search(dict, word);
 * POS: {(def != NULL) == dict_exists(dict, word)}
 */
value_t dict_search(dict_t dict, key_t word);

/** Returns true if the given word exists in the dictionary, and false
 * otherwise.
 *
 * PRE: {dict --> dict_t /\ word --> key_t}
 *   b = dict_exists(dict, word);
 * POS: {dict --> dict_t}
 */
bool dict_exists(dict_t dict, key_t word);

/** Returns the number of words contained in the dictionary.
 *
 * PRE: {dict --> dict_t}
 *  n = dict_length(dict)
 *
 */
unsigned int dict_length(dict_t dict);

/** Removes the given word from the dictionary. If
 * [word] is not in the dictionary, it does nothing and
 * returns the dict unchanged.
 *
 * PRE: {dict --> dict_t /\ word --> key_t}
 *  dict = dict_remove(dict, word);
 * POS: {dict --> dict_t /\ !dict_exists(dict, word)}
 *
 */
dict_t dict_remove(dict_t dict, key_t word);

/** Removes all the words from the dictionary.
 *
 * PRE: {dict --> dict_t}
 *  dict = dict_remove_all(dict);
 * POS: {dict --> dict_t /\ dict_length(dict) == 0}
 */
dict_t dict_remove_all(dict_t dict);

/** Prints all the words and its definitions in
 * the given file.
 *
 * Note: Use [dict_dump(dict, stdout)] to print in the screen.
 *
 * PRE: {dict --> dict_t /\ file != NULL}
 *  dict = dict_dump(dict, file);
 *
 */
void dict_dump(dict_t dict, FILE *file);

/** Destroys the given dictionary, freeing all the allocated resources.
 *
 * PRE: {dict --> dict_t}
 *   dict = dict_destroy(dict);
 * POS: {dict == NULL}
 */
dict_t dict_destroy(dict_t dict);

#endif
