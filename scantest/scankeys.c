#include "scankeys.h"

int read_matrix(const int ROWS[], const size_t NUM_ROWS,
                const int COLS[], const size_t NUM_COLS,
                int activeIndicies[][2], size_t* numActiveIndicies)
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
        pinMode(ROWS[rowIndex], OUTPUT);
        digitalWrite(ROWS[rowIndex], LOW);
    }

    /* ### MAIN LOOP ### */
    // Start with column traversal
    for (int colIndex = 0; colIndex < NUM_COLS; colIndex++)
    {

        printf("Here 5\n");

        // Save time by eliminating a ton of array accesses
        int currentColumn = COLS[colIndex];

        printf("Here 6\n");

        // If a column is LOW, a key has been pressed
        if (digitalRead(currentColumn) == LOW)
        {
            // Change the column to OUTPUT LOW and change rows to INPUTs
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

            printf("Here 7\n");
            
            for (size_t rowIndex = 0; rowIndex < NUM_ROWS; rowIndex++)
            {

                printf("Here 8\n");
                if (digitalRead(ROWS[rowIndex]) == LOW)
                {
                    printf("Here 9 %d\n", *numActiveIndicies);
                    activeIndicies[*numActiveIndicies][0] = currentColumn;
                    activeIndicies[*numActiveIndicies][1] = ROWS[rowIndex];
                    (*numActiveIndicies)++;
                    printf("Here\n");
                }
            }

            printf("Here 2\n");
            
            // Change all rows to OUTPUT LOW
            for (size_t rowIndex = 0; rowIndex < NUM_ROWS; rowIndex++)
            {
                pinMode(ROWS[rowIndex], OUTPUT);
                digitalWrite(ROWS[rowIndex], LOW);
            }

            // Change the column to INPUT PULLUP
            pinMode(currentColumn, INPUT);
            pullUpDnControl(currentColumn, PUD_UP);
        }

        printf("Here 3\n");

    }

    printf("Here 4\n");

    return *numActiveIndicies;
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