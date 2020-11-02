#ifndef USBIF_H
#define USBIF_H

/**
 * usbif.h
 * This file contains functions for interfacing with the host computer via USB
 * as a USB HID device.
 * 
 * (C) Cameron Krueger, 2020
 * Created 29 October 2020
 **/

#include <stdio.h>
#include <stddef.h>

int usb_send_data(FILE* fptr, unsigned char mods, unsigned char* keys, size_t NUM_KEYS);

int usb_receive_data(FILE* fptr, char buf[8]);

#endif
