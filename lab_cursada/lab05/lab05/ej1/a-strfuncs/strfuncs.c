#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "strfuncs.h"

size_t string_length(const char *str){
    size_t len=0;
    while (str[len] != '\0'){
        len++;
    }
    return len;
}

char * string_filter(const char *str, char c){
    
    unsigned int i = 0, j = 0, 
                 og_len = string_length(str), filter_len = 0;
    
    while (i < og_len) {
        if (str[i] != c) {
            filter_len++;
        }
        i++;
    }

    char * filtered = NULL;
    filtered = malloc(sizeof(char) * (filter_len + 1));
    if (filtered == NULL) {
        return NULL;
    }

    filtered[filter_len] = '\0';

    i = 0;
    while (i < og_len && j < filter_len) {
        if(str[i] != c){
            filtered[j] = str[i];
            j++;
        }
        i++;
    }
    return filtered;
}

bool string_is_symmetric(const char *str){
    unsigned int i = 0;
    while (i <= string_length(str)/2) {
        if(str[i] != str[string_length(str) - 1 - i]){
            return false;
        }
        i++;
    }
    
    return true;
}