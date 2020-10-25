#include "scankeys.h"

int read_matrix()
{
    
    return 0;
}




/**
 * These are less efficient than just adding the loops directly in code.
 *  These methods are sometimes called together and it would probably be more
 *  efficient to combine their contents into the same loop when this happens
 *  in code.
 */

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
