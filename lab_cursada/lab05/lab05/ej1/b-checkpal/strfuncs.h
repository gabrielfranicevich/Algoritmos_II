#ifndef _STRFUNCS_H_
#define _STRFUNCS_H

#include <stdbool.h>
#include <stddef.h>

//  calcula la longitud de la cadena apuntada por str, la función
size_t string_length(const char *str);

//  devuelve una cadena que se obtiene tomando los caracteres de ´str´ que son distintos del caracter ´c´
char *string_filter(const char *str, char c);

//  indica si la cadena apuntada por str es simétrica
bool string_is_symmetric(const char *str);

//  copies the string ´original´ into the string ´copy´
void string_copy(char *copy, char *original);

#endif