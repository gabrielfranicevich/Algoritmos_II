#ifndef _STRFUNCS_H_
#define _STRFUNCS_H_

#include <stdbool.h>

size_t string_length(const char *str);
/*
 * Returns the length of the string <s>
 *
 */


char *string_filter(const char *str, char c);
/*
 * Returns the same string without a char
 *
 */

bool string_is_symmetric(const char *str);
/*
 * Indicates if string is a palindrome
 *
 */


#endif

