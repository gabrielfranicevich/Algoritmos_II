#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"

unsigned int fstring_length(fixstring s) {
    //  se comparan todas las posiciones del fixstring hasta que alguna es igual a ´\0´, lo que representa el final
    unsigned int len = 0;
    while(s[len] != '\0'){
        len++;
    }
    return len;
}

bool fstring_eq(fixstring s1, fixstring s2) {
    //  se recorren los strings hasta encontrar un caracter diferente
    unsigned int i = 0;
    while ((s1[i] != '\0') || (s2[i] != '\0')) {
        if(s1[i] == s2[i]){
            i++;
        } else {
            //  si un caracter es diferente en ambos strings, se devuelve false
            return false;
        }
    }
    //  si no tienen caracteres diferentes, se devuelve true
    return true;    
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
    //  comparo las cadenas hasta encontrar caracteres diferentes
    unsigned int i = 0;
    while (s1[i] == s2[i]) {
        i++;
    }
    //  si s2 no es mas corta que s1, entonces chequeo cual es menor
    if (s2[i] != '\0') {
        return (s1[i] <= s2[i]);
    }
    return false;
}

void fstring_set(fixstring s1, const fixstring s2) {
    int i=0;
    while (i<FIXSTRING_MAX && s2[i]!='\0') {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
}

void fstring_swap(fixstring s1,  fixstring s2) {
    fixstring aux;
    fstring_set(aux, s1);
    fstring_set(s1, s2);
    fstring_set(s2, aux);
}