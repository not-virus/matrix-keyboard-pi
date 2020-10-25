#ifndef SCANKEYS_H
#define SCANKEYS_H

#include <stddef.h>
#include <stdio.h>
#include <wiringPi.h>

int read_matrix(const int ROWS[], const size_t NUM_ROWS,
                const int COLS[], const size_t NUM_COLS,
                int activeIndicies[][2], size_t* numActiveIndicies);

#endif
