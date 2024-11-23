#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"

//  Determina la longitud de una cadena
unsigned int fstring_length(fixstring s) {
    //  se comparan todas las posiciones del fixstring hasta que alguna es igual a ´\0´, lo que representa el final
    unsigned int i = 0;
    while(s[i] != '\0'){
        i++;
    }

    return i;
}

//  Determina si dos cadenas son iguales
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

//  Indica si la cadena guardada en s1 es menor o igual que la guardada en s2 en el sentido del orden alfabético
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