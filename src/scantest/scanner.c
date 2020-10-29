/** 
 * scan_test.c
 * 
 * This software is designed for the Raspberry Pi Zero W v1.1
 * This is a testing driver for a matrix keyboard scanner.  It returns the
 *  information regarding the keys pressed on a matrix keyboard connected to
 *  the GPIO.
 * 
 * (C) Cameron Krueger, 2020
 * Created 25 October 2020
 */

#include <wiringPi.h>
#include <stddef.h>

#include "connections.h"  // Must come before keymap
#include "keymap.h"
#include "ioif.h"

#define MAX_ACTIVE_KEYS 102 // Don't think it would even be possible to tell

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

/*
    pinMode(LED_CAPS_LOCK, OUTPUT);
    //printf("Light test started on pin %d (BCM_GPIO)\n", COL_C);
    printf("Light test started on %s, (BCM_GPIO pin %d)\n", "Caps lock", LED_CAPS_LOCK);

    for (int i = 0; i < 10; i++)
    {
        //digitalWrite(COL_C, HIGH);
        keyboard_light_on(ROW_15);
        delay(250);
        //digitalWrite(COL_C, LOW);
        keyboard_light_off(ROW_15);
        delay(250);
    }

    printf("Light test over. Please disconnect LED and press Enter to continue.\n");
    getchar();
    printf("Continuing in ");
    for (int i = 3; i > 0; i--)
    {
        printf("%d... ", i);
        fflush(stdout);
        delay(1000);
    }
    printf("\nContinuing.\n");
*/

    // Set all pins as output
    for (int pin_index = 0; pin_index < NUM_PINS; pin_index++)
    {
        pinMode(ALL_PINS[pin_index], OUTPUT);
    }

    // Set all lock LEDs to off state
    keyboard_light_off(LED_CAPS_LOCK);
    keyboard_light_off(LED_SCRL_LOCK);
    keyboard_light_off(LED_NUM_LOCK);

    /* MAIN LOOP */

    size_t numActiveKeys = 0;
    unsigned short activeKeys[MAX_ACTIVE_KEYS][2];

    int tmp = read_matrix(ROWS, NUM_ROWS, COLS, NUM_COLS, activeKeys,
                          &numActiveKeys);

    printf("\nNum active indicies: %u\n", numActiveKeys);
    printf("%d\n", tmp);

    /* Print all active indicies */
    for (int curActiveKey = 0; curActiveKey < numActiveKeys; curActiveKey++)
    {
        for (int curKey = 0; curKey < KEYMAP_COUNT; curKey++)
        {
            if (KEYMAP[curKey].hwCol == activeKeys[curActiveKey][0]
                && KEYMAP[curKey].hwRow == activeKeys[curActiveKey][1])
            {
                printf("Detected index #%u: (%u, %u)\n", curActiveKey + 1,
                activeKeys[curActiveKey][0], activeKeys[curActiveKey][1]);
                printf("Key: %s", KEYMAP[curKey].keyName);
            }

        }
    }
    
    printf("\n");
    return 0;
}