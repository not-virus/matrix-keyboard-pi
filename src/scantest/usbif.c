/**
 * usbif.c
 * Implementation file for interfacing with the host computer via USB as a USB
 * HID device.
 * 
 * (C) Cameron Krueger, 2020
 * Created 29 October 2020
 **/

#include "usbif.h"

int usb_send_data(int fd, unsigned char mods, unsigned char* keys, size_t NUM_KEYS)
{
    // Make packet buffer, initialize all fields to zero
    char buf[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

    // Write modifier data
    buf[0] = (char)mods;
    for (size_t i = 0; i < NUM_KEYS; i++)
    {
        buf[i+2] = (char)keys[i];
    }

    // Write data to file
    if (write(fd, buf, 8) != 8)
    {
        perror("Error writing to device file");
        return 1;
    }
    return 0;
}

int usb_receive_data(int fd, fd_set* readfds, char buf[8])
{
    // Initialize poll variables
    int pollRetVal = 0;
    nfds_t nfds = 1;
    struct pollfd fds[1];
    fds[0].fd = fd;
    fds[0].events = POLLIN;
    int timeout = 1;

    // Poll for data to read
    pollRetVal = poll(fds, nfds, timeout);

    // Potentially throw all kinds of errors
    if (pollRetVal == -1 && errno == EINTR)
    {
        return -1;
    }

    if (pollRetVal < 0)
    {
        perror("poll()");
        return -2;
    }

    if (pollRetVal & POLLERR || pollRetVal & POLLHUP || pollRetVal & POLLNVAL)
    {
        perror("poll() return val");
        return -3;
    }

    // If data available, read it
    int dataLen = 0;
    if (pollRetVal == POLLIN)
    {
        if (FD_ISSET(fd, readfds))
        {
            dataLen = read(fd, buf, 7);
        }
    }

    return dataLen;
}