#ifndef _ARRAY_HELPERS_H
#define _ARRAY_HELPERS_H

#include <stdbool.h>

#include "fixstring.h"

/*
    Return whether the array 'other' is a permutation of the array 'a'.

    The arrays 'a' and 'other' must have both the same 'length'.
 */
bool array_is_permutation_of(fixstring a[], fixstring other[], unsigned int length);

/*
    Write the content of the array 'a' into stdout. The array 'a' must have
    exactly 'length' elements.
 */
void array_dump(fixstring a[], unsigned int length);

/* 
   Copy the array 'src' into the array 'dst' 
 */
void array_copy(fixstring dst[], fixstring src[], unsigned int length);

/**
 * Reads an array of strings from a file and stores them in the provided array.
 * 
 * The input file must follow this format:
 * 
 * ```
 * <array_length>
 * <array_elem_1> <array_elem_2> <array_elem_3> ... <array_elem_N>
 * ```
 * 
 * - The first line specifies the total number of elements in the array (`array_length`).
 * 
 * - The second line contains the array elements, separated by one or more whitespace characters.
 * 
 * Requirements:
 * 
 * - The value of `array_length` in the file must not exceed `max_size`.
 * 
 * - Each element read from the file is copied into the provided array `a`.
 * 
 * @param a        The array where the elements will be stored.
 * @param max_size The maximum size of the array `a`.
 * @param filepath Path to the file containing the array data.
 * @returns The actual number of elements successfully read and stored in the array.
 */
unsigned int array_from_file(fixstring a[], unsigned int max_size, const char *filepath);

#endif
