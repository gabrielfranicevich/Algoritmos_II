#ifndef _WEATHER_UTILS_H
#define _WEATHER_UTILS_H

#include <stdio.h>
#include "array_helpers.h"
#include "weather.h"

/**
 * Menor temperatura minima historica registrada en la ciudad de cba
 */
int minmintemp(WeatherTable date);

/**
 * registra para cada año entre 1980 y 2016 la mayor temp maxima
 */
void procedimiento(WeatherTable a, int output[YEARS]);

/**
 * registr para cada año entre 1980 y 2016 el mes de ese año que se registro la mayor cantidad de precipitaciones
 */
void mes_max_prec(WeatherTable date, month_t output[YEARS]);

#endif

/*
  @file weather_utils.h
*/