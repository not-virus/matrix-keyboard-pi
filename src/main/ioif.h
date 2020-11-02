/**
 * ioif.h
 * This file contains functions for interfacing with the matrix keyboard and
 *  other hardware through the GPIO
 * 
 * (C) Cameron Krueger, 2020
 * Created 25 October 2020
 */

#ifndef IOIF_H
#define IOIF_H

#include <wiringPi.h>
#include <stddef.h>
#include <stdio.h>

int read_matrix(const unsigned short ROWS[], const size_t NUM_ROWS,
                const unsigned short COLS[], const size_t NUM_COLS,
                unsigned short activeIndicies[][2], size_t* numActiveIndicies);

void keyboard_light_on(const unsigned short lightPin);

void keyboard_light_off(const unsigned short lightPin);

#endif
