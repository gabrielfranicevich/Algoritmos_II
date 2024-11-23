/*
  @file main.c
  @brief Defines main program function
*/
/* 
weather_cordoba.in

1980 1 1 211 290 130 10130 54 0
1980 1 2 218 310 120 10070 53 0
1980 1 3 247 320 160 10058 51 0

Las primeras 3 columnas corresponden a año, mes y dia
Las restantes 6 son temp media, maxima, minima, presion atmos, humedad y precipitaciones

Las temperaturas estan medidas en grados centigrados, pero expresadas en decimas
La presion multiplicada por 10 y las precipitaciones por 100
*/

/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "array_helpers.h"

/**
 * @brief print usage help
 * @param[in] program_name Executable name
 */
void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Load climate data from a given file in disk.\n"
           "\n"
           "The input file must exist in disk and every line in it must have the following format:\n\n"
           "<year> <month> <day> <temperature> <high> <low> <pressure> <moisture> <precipitations>\n\n"
           "Those elements must be integers and will be copied into the multidimensional integer array 'a'.\n"
           "The dimensions of the array are given by the macro tclimate.\n"
           "\n\n",
           program_name);
}

/**
 * @brief reads file path from command line
 *
 * @param[in] argc amount of command line arguments
 * @param[in] argv command line arguments
 *
 * @return An string containing read filepath
 */
char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

/**
 * @brief Main program function
 *
 * @param[in] argc amount of command line arguments
 * @param[in] argv command line arguments
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* create an array with the type of tclimate */
    WeatherTable array;

    /* parse the file to fill the array and obtain the actual length */
    array_from_file(array, filepath);

    /* show the ordered array in the screen */
    array_dump(array);

    //Parte b
        // 1
    printf("la menor temperatura minima fue:%d\n",minmintemp(array));
        //2
    int i=0, año=FST_YEAR , out[YEARS];
    procedimiento(array, out);
    printf("la temperatura minima en cada año fue:\n[");
    while (i<YEARS-1)
    {
        printf("%d: %d, ", año, out[i]);
        i=i+1; año=año+1;
    }
    printf("%d: %d]\n", año, out[i]);
        //3
    año=FST_YEAR, i=0;
    month_t output[YEARS];
    mes_max_prec(array, output);
    printf("el mes con mas precipitaciones en cada año fue:\n[");
    while (i<YEARS-1)
    {
        printf("%d: %d, ", año, output[i]);
        i=i+1; año=año+1;
    }
    printf("%d: %d]\n", año, output[i]);


    return (EXIT_SUCCESS);
}
