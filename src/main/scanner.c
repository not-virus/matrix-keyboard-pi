/** 
 * scan_test.c
 * 
 * This software is designed for the Raspberry Pi Zero W v1.1
 * This is a USB HID device controller driver for a matrix keyboard.  It scans
 *  a keyboard matrix conndcted to the GPIO and sends the typed values to the
 *  /dev/hidg0 raw file for a device set up as a USB HID Linux gadget.
 * 
 * (C) Cameron Krueger, 2020
 * Created 25 October 2020
 */

#include <wiringPi.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include "connections.h"  // Must come before keymap
#include "keymap.h"
#include "ioif.h"
#include "usbif.h"

#define MAX_PRESSED_KEYS 102
#define MAX_ACTIVE_KEYS 6

void bin(char n);

int main()
{
    // GPIO Setup
    if (wiringPiSetupGpio() == -1)
    {
        return 1;
    }
    printf("GPIO setup successful.\n");


    // Device file setup
    const char* fname = "/dev/hidg0";
    int fd = 0;
    int outReportLen;
    fd_set readfds;

    if ((fd = open(fname, O_RDWR, 0666)) == -1)
    {
        perror(fname);
        return 2;  // Return with error
    }


    // Set all pins as output
    for (int pin_index = 0; pin_index < NUM_PINS; pin_index++)
    {
        pinMode(ALL_PINS[pin_index], OUTPUT);
    }

    // Set all lock LEDs to off state
    keyboard_light_off(LED_CAPS_LOCK);
    keyboard_light_off(LED_SCRL_LOCK);
    keyboard_light_off(LED_NUM_LOCK);

    // The read buffer. Will hold data read in from host device output reports
    char buf[] = {0,0,0,0,0,0,0,0};

    // Flag set when a packet has been written to the hidg0 device file and the
    //  packet data needs to be cleared
    unsigned char clearNeeded = 0;

    // Size of output report from device in bytes
    int outputReportSize = 0;

    /* MAIN LOOP */
    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);

        size_t numPressedKeys = 0;
        unsigned short pressedKeys[MAX_PRESSED_KEYS][2];

        // Scan matrix
        read_matrix(ROWS, NUM_ROWS, COLS, NUM_COLS, pressedKeys,
                    &numPressedKeys);

        size_t numActiveKeys = 0;
        struct Key activeKeys[MAX_ACTIVE_KEYS];
        unsigned char activeKeys_codesOnly[MAX_ACTIVE_KEYS];
        unsigned char activeModifiers = 0x00; // Reset active modifiers

        // Agregate pressed keys into activeKeys and activeModifiers
        for (size_t curPressedKey = 0; curPressedKey < numPressedKeys;
            curPressedKey++)
        {
            for (size_t curKey = 0; curKey < KEYMAP_COUNT; curKey++)
            {
                if (KEYMAP[curKey].hwCol == pressedKeys[curPressedKey][0]
                    && KEYMAP[curKey].hwRow == pressedKeys[curPressedKey][1])
                {                    
                    // Add modifier
                    activeModifiers |= KEYMAP[curKey].modBit;

                    int isInActiveKeys = 0;
                    // Check to see if current key is already in list of active
                    //  keys
                    for (size_t i = 0; i < numActiveKeys; i++)
                    {
                        isInActiveKeys = (activeKeys[i].keyID
                            == KEYMAP[curKey].keyID);
                        if (isInActiveKeys) break;
                    }

                    // If not already present, add to list of active keys
                    if (!isInActiveKeys && numActiveKeys < MAX_ACTIVE_KEYS)
                    {
                        activeKeys[numActiveKeys] = KEYMAP[curKey];
                        activeKeys_codesOnly[numActiveKeys]
                            = KEYMAP[curKey].hidCode;
                        numActiveKeys++;
                    }
                    // If more than MAX_ACTIVE_KEYS (6) pressed, send error
                    //  code by setting all to 0x01
                    else if (numActiveKeys >= MAX_ACTIVE_KEYS)
                    {
                        for (int i = 0; i < MAX_ACTIVE_KEYS; i++)
                        {
                            activeKeys[i] = KEYMAP[INDEX_ERROR_KEY];
                        }
                    }
                }
            }
        }

        /* HOTFIX, PLEASE REVISE!! */

        // Remove TAB key if W, A, and D are being pressed and remove Q key if
        // W, S, and D are being pressed.
        char wPressed = 0;
        char aPressed = 0;
        char sPressed = 0;
        char dPressed = 0;
        for (int i = 0; i < numActiveKeys; i++)
        {
            if (activeKeys_codesOnly[i] == 0x1A)
            {
                wPressed = 1;
            }
            if (activeKeys_codesOnly[i] == 0x04)
            {
                aPressed = 1;
            }
            if (activeKeys_codesOnly[i] == 0x16)
            {
                sPressed = 1;
            }
            if (activeKeys_codesOnly[i] == 0x07)
            {
                dPressed = 1;
            }
        }
        if ((wPressed && aPressed && dPressed)
            || (wPressed && sPressed && dPressed))
        {
            for (int i = 0; i < numActiveKeys; i++)
            {
                if (activeKeys_codesOnly[i] == 0x2B)   // If TAB key
                {
                    activeKeys_codesOnly[i] = EMPTY_KEY.hidCode;
                }
                if (activeKeys_codesOnly[i] == 0x14)   // If Q key
                {
                    activeKeys_codesOnly[i] = EMPTY_KEY.hidCode;
                }
            }
        }

        /* END HOTFIX */


        // Send key data packet to host
        if (numActiveKeys != 0)
        {
            outputReportSize = usb_receive_data(fd, &readfds, buf);
            unsigned char writeSuccess = usb_send_data(fd, activeModifiers,
                activeKeys_codesOnly, numActiveKeys);

            if (writeSuccess != 0)
            {
                printf("Write error: %d\n", writeSuccess);
                return 2;
            }
            if (outputReportSize < 0)
            {
                printf("Read error: %d\n", outputReportSize);
                return 2;
            }

            clearNeeded = 1;
        }
        // Send "no data" packet, if necessary
        else if (clearNeeded)
        {
            outputReportSize = usb_receive_data(fd, &readfds, buf);
            unsigned char writeSuccess = usb_send_data(fd, 0,
                activeKeys_codesOnly, 0);
            
            if (writeSuccess != 0)
            {
                printf("Write error: %d\n", writeSuccess);
                return 2;
            }
            if (outputReportSize < 0)
            {
                printf("Read error: %d\n", outputReportSize);
                return 2;
            }

            clearNeeded = 0;
        }
        // Read output report, if one is available
        else
        {
            outputReportSize = usb_receive_data(fd, &readfds, buf);
            if (outputReportSize < 0)
            {
                printf("Read error: %d\n", outputReportSize);
                return 2;
            }
        }

        // LED control
        if (buf[0] & 0b1)
        {
            keyboard_light_on(LED_NUM_LOCK);
        }
        else
        {
            keyboard_light_off(LED_NUM_LOCK);
        }

        if (buf[0] & 0b10)
        {
            keyboard_light_on(LED_CAPS_LOCK);
        }
        else
        {
            keyboard_light_off(LED_CAPS_LOCK);
        }
        
        if (buf[0] & 0b100)
        {
            keyboard_light_on(LED_SCRL_LOCK);
        }
        else
        {
            keyboard_light_off(LED_SCRL_LOCK);
        }
    }

    close(fd);
    return 0;
}