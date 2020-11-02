/**
 * usbif.c
 * Implementation file for interfacing with the host computer via USB as a USB
 * HID device.
 * 
 * (C) Cameron Krueger, 2020
 * Created 29 October 2020
 **/

#include "usbif.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int usb_send_data(FILE* fptr, unsigned char mods, unsigned char* keys, size_t NUM_KEYS)
{
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
    fflush(fptr);
    //fclose(fptr);
    return 0;
}

int usb_receive_data(FILE* fptr, char buf[8])
{
    if (fptr != NULL) {
        fflush(fptr);
        fseek(fptr, 0, SEEK_SET);
        if (fseek(fptr, 0, SEEK_SET) != -1)
        {
            // This shouldn't work, but I'm going to try anyway
            fread(&buf[0], sizeof(buf[0]), 1, fptr);
            return 0;

            int size = ftell(fptr);

            if (size == 0) {
                //printf("File is empty\n");
                return 1;
            }
            else
            {
                printf("Found data!\n");
/*
                char c;
                size_t bufIndex = 0;
                while ((c = fgetc(fptr)) != EOF && bufIndex < 8)
                {
                    buf[bufIndex] = c;
                    bufIndex++;
                    printf("%c, ", c);
                }
                printf("\n");
*/
                return 0;
            }
        } 
        else
        {
            perror("Seek error!");
            int e = errno;
            printf("Errno: %d\n", e);
            fclose(fptr);
            return 2;
        }

    return 3;
    }

    // Read data from file
    /*fscanf(fptr, "%c%c%c%c%c%c%c%c", buf[0], buf[1], buf[2], buf[3], buf[4],
            buf[5], buf[6], buf[7]);*/

    //fflush(fptr);
    //fclose(fptr);

    /*
    int fd = 0;
    fd = open(fname, O_RDWR, 0666);

    int i;
    int cmd_len;
    fd_set rfds;

    FD_SET(fd, &rfds);

    if (FD_ISSET(fd, &rfds)) {
        //printf("True\n");
        cmd_len = read(fd, buf, 8 - 1);
        //printf("recv report:");
        //for (i = 0; i < cmd_len; i++)
            //printf(" %02x", buf[i]);
    }

    close(fd);
    */
    return 0;
}