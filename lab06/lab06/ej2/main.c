#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "string.h"


int main(int argc, char *argv[]){
    if(argc<3){
        exit(EXIT_FAILURE);
    }
    
    char *str1=argv[1];
    char *str2=argv[2];
    bool res;
    string word1=string_create(str1);
    string word2=string_create(str2);
    res=string_less(word1, word2);
    if(res==true){
        printf("La primera cadena es menor que la segunda.\n");
    }else if(res==false){
        res=string_eq(word1,word2);
        if(res==true){
            printf("Ambas cadenas son iguales.\n");
        }else{
            printf("La primera cadena es mayor que la segunda.\n");
        }
    }
    string_destroy(word1);
    string_destroy(word2);
    return EXIT_SUCCESS;
}
