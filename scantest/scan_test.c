/**
 * (C) Cameron Krueger, 2020
 * 
 * This software is designed for the Raspberry Pi Zero W v1.1
 * This is a matrix keyboard scanner.  It returns the values of the keys
 *  pressed on a matrix keyboard connected to the GPIO.
 */

#include <wiringPi.h>
#include <stddef.h>

#include "connections.h"
#include "keymap.h"
#include "scankeys.h"

/*  MAY NOT BE NECESSARY
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>*/

int main()
{
    if (wiringPiSetupGpio() == -1)
    {
        return 1;
    }

    /* Set all pins as output */
    for (int pin_index = 0; pin_index < NUM_PINS; pin_index++)
    {
        pinMode(ALL_PINS[pin_index], OUTPUT);
    }

    read_matrix(ROWS, NUM_ROWS, COLS, NUM_COLS);

    return 0;
}