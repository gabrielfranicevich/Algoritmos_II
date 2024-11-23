#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "strfuncs.h"

size_t string_length(const char *str){
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

char *string_filter(const char *str, char c){
    size_t len = string_length(str);
    char *nret = malloc((len + 1) * sizeof(char));
    size_t j=0;
    for (size_t i = 0; i < string_length(str); i++)
    {
        if (str[i]!=c)
        {
            nret[j]=str[i];
            j++;
        }
    }
    nret[j] = '\0';
    return nret;   
}

bool string_is_symmetric(const char *str){
    for (size_t i = 0; i < string_length(str)/2; i++)
    {
        if (str[i]!=str[string_length(str)-(i+1)])
        {
            return false;
        }
        
    }
    return true;
}