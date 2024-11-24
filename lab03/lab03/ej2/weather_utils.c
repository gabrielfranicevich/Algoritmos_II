/*
  @file weather_utils.c
*/
#include <stdbool.h>
#include "array_helpers.h"
#include "weather_utils.h"
#include <limits.h>
#include <stdio.h>
#include "weather.h"


int minmintemp(WeatherTable date) {
    int res = __INT_MAX__;
    unsigned int year = 0u;
    while (year < YEARS) {

        unsigned int month =0u;
        while (month < MONTHS) {

            unsigned int day = 0u;
            while (day < DAYS){
                day = day + 1;
                Weather fecha = date[year][month][day];
                if (fecha._min_temp < res) {
                    res = fecha._min_temp;
                }
            }
            month = month + 1;
        }
        year = year + 1;
    }
  return res;
}

void procedimiento(WeatherTable date, int output[YEARS]) {
    int res = -2147483648;
    int year = 0;
    while (year < YEARS) {
        int month = 0;
        while (month < MONTHS) {
    
            int day = 0;
            while (day < DAYS) {
    
                Weather fecha = date[year][month][day];
                if (fecha._max_temp > res) {
                    
                    res = fecha._max_temp;
                }
                day = day + 1;
            }
            month = month + 1;
        }
        output[year] = res;
        year = year + 1;
    }
}

void mes_max_prec(WeatherTable date, month_t output[YEARS]) {
    unsigned int year = 0u;
    while (year < YEARS) {
        unsigned int month = 0u;
        unsigned int res = 0u;
        month_t mes = 0;
        while (month < MONTHS) {
            unsigned int day = 0u;
            while (day < DAYS) {
                Weather fecha = date[year][month][day];
                if (fecha._rainfall > res) {
                    res = fecha._rainfall;
                    mes = month;
                }
                day = day + 1;
            }
            month = month + 1;
        }
        output[year] = mes;
        year = year + 1;
    }
}