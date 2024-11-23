#ifndef _WEATHER_UTILS_H
#define _WEATHER_UTILS_H

#include "array_helpers.h"

int minmintemp(WeatherTable date);
/*
Menor temperatura minima historica registrada en la ciudad de cba
*/

void procedimiento(WeatherTable a, int output[YEARS]);
/*
 registra para cada año entre 1980 y 2016 la mayor temp maxima
*/

void mes_max_prec(WeatherTable date, month_t output[YEARS]);
/*
registr para cada año entre 1980 y 2016 el mes de ese año que se registro la mayor cantidad de precipitaciones
*/

#endif

/*
  @file weather_utils.h
*/
#include <stdio.h>
#include "array_helpers.h"



