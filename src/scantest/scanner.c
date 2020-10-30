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
#include "usbif.h"

#define MAX_PRESSED_KEYS 102 // Don't think it would even be possible to tell
#define MAX_ACTIVE_KEYS 6

/*  MAY NOT BE NECESSARY
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>*/

void bin(unsigned char n);

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

    size_t numPressedKeys = 0;
    unsigned short pressedKeys[MAX_PRESSED_KEYS][2];

    read_matrix(ROWS, NUM_ROWS, COLS, NUM_COLS, pressedKeys,
                          &numPressedKeys);

    printf("\nNum pressed indicies: %u\n", numPressedKeys);

    size_t numActiveKeys = 0;
    struct Key activeKeys[MAX_ACTIVE_KEYS];
    unsigned char activeKeys_codesOnly[MAX_ACTIVE_KEYS];
    unsigned char activeModifiers = 0x00; // Reset active modifiers

    /* Print all pressed keys */
    for (size_t curPressedKey = 0; curPressedKey < numPressedKeys; curPressedKey++)
    {
        for (size_t curKey = 0; curKey < KEYMAP_COUNT; curKey++)
        {
            if (KEYMAP[curKey].hwCol == pressedKeys[curPressedKey][0]
                && KEYMAP[curKey].hwRow == pressedKeys[curPressedKey][1])
            {
                printf("Detected index #%u: (%u, %u)\n", curPressedKey + 1,
                pressedKeys[curPressedKey][0], pressedKeys[curPressedKey][1]);
                printf("Key: %s\n", KEYMAP[curKey].keyName);
                
                // Add modifier
                activeModifiers = activeModifiers | (1 << 3);//KEYMAP[curKey].modBit);

                int isInActiveKeys = 0;
                // check to see if current key is already in list of active keys
                for (size_t i = 0; i < numActiveKeys; i++)
                {
                    isInActiveKeys = (activeKeys[i].keyID == KEYMAP[curKey].keyID);
                    printf("%d\n", isInActiveKeys);
                    if (isInActiveKeys) break;
                }

                // If not already present, add to list of active keys
                if (!isInActiveKeys && numActiveKeys < MAX_ACTIVE_KEYS)
                {
                    activeKeys[numActiveKeys] = KEYMAP[curKey];
                    activeKeys_codesOnly[numActiveKeys] = KEYMAP[curKey].hidCode;
                    numActiveKeys++;
                }
            }
        }
    }

    // Print active modifiers
    printf("Active modifiers: 0x%02x  0b", activeModifiers);
    bin(activeModifiers);
    printf("\n");

    // Print list of active keys
    printf("Active keys: ");
    for (size_t i = 0; i < numActiveKeys; i++)
    {
        printf("%s, ", activeKeys[i].keyName);
    }
    printf("\n");

    printf("\n");
    usb_send_data(activeModifiers, activeKeys_codesOnly, numActiveKeys);
    usb_send_data(0, activeKeys_codesOnly, 0);
    printf("\n");

    printf("\n");
    return 0;
}

void bin(unsigned char n)
{
    unsigned i;
    for (i = 1 << 7; i > 0; i = i / 2)
        (n & i)? printf("1"): printf("0");
}