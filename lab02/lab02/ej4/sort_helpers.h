/**
 *
 * Author   2017 Daniel Fridlender
 *
 * Revision 2018 Sergio Canchi
 *
 *
 */
#ifndef _SORT_HELPERS_H
#define _SORT_HELPERS_H

#include <stdbool.h>

/* Abstract total order for sorting algorithms */
bool goes_before(int x, int y);

/* Checks if the array 'a' is in ascending order */
bool array_is_sorted(int a[], unsigned int length);

/** 
 * Exchanges elements of array 'a' in the given positions 'i' and 'j'
 * Array remains the same if the two positions are the same
 */
void swap(int a[], unsigned int i, unsigned int j);

/* Resets the comparisons_counter */
void reset_comparisons_counter();

/* Returns value of comparisons_counter*/
unsigned int comparisons_number();

/* Resets the counter of swaps */
void reset_swaps_counter();

/* Returns value of swaps_counter*/
unsigned int swaps_number();

/* Initialize the current time */
void set_current_time();

/* Calculate the time elapsed in milliseconds */
double calculate_elapsed_time();


#endif
