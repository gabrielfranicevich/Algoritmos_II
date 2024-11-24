/*
  @file weather.c
  @brief Implements weather mesuarement structure and methods
*/
#include <stdlib.h>
#include "weather.h"

static const int AMOUNT_OF_WEATHER_VARS = 6 ;

Weather weather_from_file(FILE* file) {
    Weather weather;
    int res = fscanf(file, "%d %d %d %u %u %u", &weather._average_temp,
                                                &weather._max_temp,
                                                &weather._min_temp,
                                                &weather._pressure,
                                                &weather._moisture,
                                                &weather._rainfall);

    if(res != AMOUNT_OF_WEATHER_VARS) {
        fprintf(stderr, "amount of weather vars are incorrect");
    }
    return weather;
}

void weather_to_file(FILE* file, Weather weather) {
    //  escribe la entrada EXPECTED_WEATHER_INPUT, con el formato EXPECTED_WEATHER_FILE_FORMAT
    //  en el achivo file
    fprintf(file, EXPECTED_WEATHER_FILE_FORMAT, EXPECTED_WEATHER_INPUT);
}
