/**
 * usbif.c
 * Implementation file for interfacing with the host computer via USB as a USB
 * HID device.
 * 
 * (C) Cameron Krueger, 2020
 * Created 29 October 2020
 **/

#include "usbif.h"

int usb_send_data(unsigned char mods, unsigned char* keys, size_t NUM_KEYS)
{
    const char* fname = "./TestFile";//"/dev/hidg0";
    FILE* fptr;
    if ((fptr = fopen(fname, "wb")) == NULL)
    {
        fprintf(stderr, "Error! Couldn't open %s for writing.", fname);
        // Return error
        return 1;
    }

    // Make packet buffer, initialize all fields to zero
    char buf[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

    // Write modifier data
    buf[0] = (char)mods;
    for (size_t i = 0; i < NUM_KEYS; i++)
    {
        buf[i+2] = (char)keys[i];
    }

    // Print data to file
    fprintf(fptr, "%c%c%c%c%c%c%c%c", buf[0], buf[1], buf[2], buf[3],
             buf[4], buf[5], buf[6], buf[7]);
    //fflush(fptr);
    fclose(fptr);
    return 0;
}

int usb_receive_data(char buf[8])
{
    const char* fname = "./TestFile";//"/dev/hidg0";
    FILE* fptr;
    if ((fptr = fopen(fname, "rb")) == NULL)
    {
        fprintf(stderr, "Error! Couldn't open %s for writing.", fname);
        // Return error
        return 1;
    }

    // Read data from file
    fscanf(fptr, "%c%c%c%c%c%c%c%c", buf[0], buf[1], buf[2], buf[3],
            buf[4], buf[5], buf[6], buf[7]);
    //fflush(fptr);
    fclose(fptr);
    return 0;
}