/**
 * ioif.c
 * ioif - input/output interface
 *  ("ioctl" is an established syscall, so "ioif" it is)
 * 
 * This is the implementation file for interfacing with the matrix keyboard
 *  and other hardware through the GPIO
 * 
 * (C) Cameron Krueger, 2020
 * Created 25 October 2020
 */

#include "ioif.h"

int read_matrix(const unsigned short ROWS[], const size_t NUM_ROWS,
                const unsigned short COLS[], const size_t NUM_COLS,
                unsigned short activeIndicies[][2], size_t* numActiveIndicies)
{
    // Reset active indicies array by resetting counter
    *numActiveIndicies = 0;

    // Set all columns to INPUTs with PULLUPs
    for (size_t colIndex = 0; colIndex < NUM_COLS; colIndex++)
    {
        pinMode(COLS[colIndex], INPUT);
        pullUpDnControl(COLS[colIndex], PUD_UP);
    }
    // Set all rows to OUTPUTs and set output value to LOW
    for (size_t rowIndex = 0; rowIndex < NUM_COLS; rowIndex++)
    {
        pullUpDnControl(ROWS[rowIndex], PUD_OFF);
        pinMode(ROWS[rowIndex], OUTPUT);
        digitalWrite(ROWS[rowIndex], LOW);
    }

    /* ### MAIN LOOP ### */
    // Start with column traversal
    for (int colIndex = 0; colIndex < NUM_COLS; colIndex++)
    {

        // Save time by eliminating repeated array accesses
        int currentColumn = COLS[colIndex];

        // If a column is LOW, a key has been pressed
        if (digitalRead(currentColumn) == LOW)
        {
            // Change the column to OUTPUT LOW and change rows to INPUTs
            pullUpDnControl(currentColumn, PUD_OFF);
            pinMode(currentColumn, OUTPUT);
            digitalWrite(currentColumn, LOW);
            
            // Change all rows to INPUT PULLUPs (this would be computationally)
            //  equivalent to performing the same change in the next loop for
            //  each pin just before it's checked, but this rapid
            //  change-then-check could introduce potential electrical issues
            for (size_t rowIndex = 0; rowIndex < NUM_ROWS; rowIndex++)
            {
                pinMode(ROWS[rowIndex], INPUT);
                pullUpDnControl(ROWS[rowIndex], PUD_UP);
            }

            for (size_t rowIndex = 0; rowIndex < NUM_ROWS; rowIndex++)
            {
                // If current row is pulled LOW, add row, column pair to
                //  activeIndicies
                if (digitalRead(ROWS[rowIndex]) == LOW)
                {
                    activeIndicies[*numActiveIndicies][0] = currentColumn;
                    activeIndicies[*numActiveIndicies][1] = ROWS[rowIndex];
                    (*numActiveIndicies)++;
                }
            }

            // Change all rows to OUTPUT LOW
            for (size_t rowIndex = 0; rowIndex < NUM_ROWS; rowIndex++)
            {
                pullUpDnControl(ROWS[rowIndex], PUD_OFF);
                pinMode(ROWS[rowIndex], OUTPUT);
                digitalWrite(ROWS[rowIndex], LOW);
            }

            // Change the column to INPUT PULLUP
            pinMode(currentColumn, INPUT);
            pullUpDnControl(currentColumn, PUD_UP);
        }

    }

    return *numActiveIndicies;
}



/**
 * Turns a keyboard LED on.  Assumes lightPin has already been set to OUTPUT.
 */
/*
void keyboard_light_on(const unsigned short LED_PIN)
{
    // If common anode, set pin LOW. Otherwise, set HIGH.
    #ifdef LEDS_COM_ANODE
        digitalWrite(LED_PIN, LOW);
    #elif LEDS_COM_CATHODE
        digitalWrite(LED_PIN, HIGH);
    #else
        #error "Warning! LEDS_COM_(ANODE/CATHODE) was not defined! Cannot control LEDs."
    #endif
    
}*/

/**
 * Turns a keyboard LED off.  Assumes lightPin has already been set to OUTPUT.
 */
/*
void keyboard_light_off(const unsigned short LED_PIN)
{
    // If common anode, set pin HIGH. Otherwise, set LOW.
    #ifdef LEDS_COM_ANODE
        digitalWrite(LED_PIN, HIGH);
    #elif LEDS_COM_CATHODE
        digitalWrite(LED_PIN, LOW);
    #else
        #error "Warning! LEDS_COM_(ANODE/CATHODE) was not defined! Cannot control LEDs."
    #endif
}




/**
 * These are less efficient than just adding the loops directly in code.
 *  These methods are sometimes called together and it would probably be more
 *  efficient to combine their contents into the same loop when this happens
 *  in code.
 */

/*
void _set_all_rows_mode(int mode)
{
    for(int row_index = 0; row_index < NUM_ROWS; row_index++)
    {
        pinMode(ROWS[row_index], mode);
    }
}

void _set_all_rows_value(int value)
{
    for(int row_index = 0; row_index < NUM_ROWS; row_index++)
    {
        digitalWrite(ROWS[row_index], value);
    }
}
*/