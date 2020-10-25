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

#define MAX_ACTIVE_KEYS 104 // Don't think it would even be possible to tell

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

    printf("GPIO setup successful.\n");

    /* Set all pins as output */
    for (int pin_index = 0; pin_index < NUM_PINS; pin_index++)
    {
        pinMode(ALL_PINS[pin_index], OUTPUT);
    }

    size_t numActiveKeys = 0;
    int activeKeys[MAX_ACTIVE_KEYS][2];

    int tmp = read_matrix(ROWS, NUM_ROWS, COLS, NUM_COLS, activeKeys, &numActiveKeys);

    printf("\nTmp: %d\n", numActiveKeys);
    
    printf("\n");
    return 0;
}