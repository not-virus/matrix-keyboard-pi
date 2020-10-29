#ifndef KEYMAP_H
#define KEYMAP_H

#include "connections.h"

struct Key {
    unsigned char hwCol;
    unsigned char hwRow;
    char*  keyName;
    //char*  hidCode;
};

// Pin assignment for keyboard lock LEDs.
#define LED_CAPS_LOCK ROW_15
#define LED_SCRL_LOCK ROW_9
#define LED_NUM_LOCK ROW_6

// Format for keymap is based on matrix defined in connections.h:
//  i.e. if you have 
const size_t KEYMAP_COUNT = 101;
const struct Key KEYMAP[] = {
    {COL_H, ROW_14, "ESC"},
    {COL_G, ROW_14, "F1"}, 
    {COL_F, ROW_14, "F2"},
    {COL_E, ROW_14, "F3"},
    {COL_D, ROW_14, "F4"},
    {COL_C, ROW_14, "F5"},
    {COL_B, ROW_14, "F6"},
    {COL_A, ROW_14, "F7"},
    {COL_G, ROW_8, "F8"},
    {COL_F, ROW_8, "F9"},
    {COL_E, ROW_8, "F10"},
    {COL_D, ROW_8, "F11"},
    {COL_C, ROW_8, "F12"},
    {COL_F, ROW_5, "PRINT SC"},
    {COL_B, ROW_8, "SC LOCK"},
    {COL_A, ROW_8, "PAUSE/BR"},
    {COL_H, ROW_13, "~"},
    {COL_G, ROW_13, "1"},
    {COL_F, ROW_13, "2"},
    {COL_E, ROW_13, "3"},
    {COL_D, ROW_13, "4"},
    {COL_C, ROW_13, "5"},
    {COL_B, ROW_13, "6"},
    {COL_A, ROW_13, "7"},
    {COL_H, ROW_7, "8"},
    {COL_G, ROW_7, "9"},
    {COL_F, ROW_7, "0"},
    {COL_E, ROW_7, "-"},
    {COL_D, ROW_7, "="},
    {COL_C, ROW_7, "BKSPC"},
    {COL_A, ROW_1, "INSERT"},
    {COL_H, ROW_5, "HOME"},
    {COL_G, ROW_5, "PAGE UP"},
    {COL_C, ROW_5, "NUM"},
    {COL_A, ROW_5, "num /"},
    {COL_B, ROW_4, "num *"},
    {COL_A, ROW_4, "num -"},
    {COL_H, ROW_12, "TAB"},
    {COL_G, ROW_12, "Q"},
    {COL_F, ROW_12, "W"},
    {COL_E, ROW_12, "E"},
    {COL_D, ROW_12, "R"},
    {COL_C, ROW_12, "T"},
    {COL_B, ROW_12, "Y"},
    {COL_A, ROW_12, "U"},
    {COL_B, ROW_7, "I"},
    {COL_A, ROW_7, "O"},
    {COL_H, ROW_8, "P"},
    {COL_H, ROW_4, "["},
    {COL_G, ROW_4, "]"},
    {COL_F, ROW_4, "\\"},
    {COL_D, ROW_1, "DEL"},
    {COL_C, ROW_1, "END"},
    {COL_B, ROW_1, "PAGE DN"},
    {COL_E, ROW_4, "num 7"},
    {COL_D, ROW_4, "num 8"},
    {COL_C, ROW_4, "num 9"},
    {COL_A, ROW_3, "num +"},
    {COL_E, ROW_5, "CAPS"},
    {COL_H, ROW_11, "A"},
    {COL_G, ROW_11, "S"},
    {COL_F, ROW_11, "D"},
    {COL_E, ROW_11, "F"},
    {COL_D, ROW_11, "G"},
    {COL_C, ROW_11, "H"},
    {COL_B, ROW_11, "J"},
    {COL_A, ROW_11, "K"},
    {COL_H, ROW_3, "L"},
    {COL_G, ROW_3, ";"},
    {COL_F, ROW_3, "'"},
    {COL_E, ROW_2, "ENTER"},
    {COL_D, ROW_3, "num 4"},
    {COL_C, ROW_3, "num 5"},
    {COL_B, ROW_3, "num 6"},
    {COL_F, ROW_18, "L SHIFT"},
    {COL_H, ROW_16, "Z"},
    {COL_G, ROW_16, "X"},
    {COL_F, ROW_16, "C"},
    {COL_E, ROW_16, "V"},
    {COL_D, ROW_16, "B"},
    {COL_C, ROW_16, "N"},
    {COL_B, ROW_16, "M"},
    {COL_A, ROW_16, ","},
    {COL_H, ROW_2, "."},
    {COL_G, ROW_2, "/"},
    {COL_E, ROW_18, "R SHIFT"},
    {COL_E, ROW_1, "ARR UP"},
    {COL_C, ROW_2, "num 1"},
    {COL_B, ROW_2, "num 2"},
    {COL_A, ROW_2, "num 3"},
    {COL_B, ROW_5, "num ENTER"},
    {COL_H, ROW_19, "L CTRL"},
//    { "L WIN"},
    {COL_H, ROW_17, "L ALT"},
    {COL_F, ROW_2, "SPACE"},
    {COL_D, ROW_5, "R ALT"},
//    { "R WIN"},
//    { "MENU"},
    {COL_C, ROW_19, "R CTRL"},
    {COL_H, ROW_1, "ARR LEFT"},
    {COL_G, ROW_1, "ARR DOWN"},
    {COL_F, ROW_1, "ARR RIGHT"},
    {COL_E, ROW_2, "num 0"},
    {COL_D, ROW_2, "num ."}
};

/**
 * Okay, keymap needs to be a two dimensional array which matches the layout of the
 * keyboard. Then, rearrange the orders of the row and column arrays such that the
 * indicies of the values in the row and column arrays can also be used to index the
 * keyap.
 */

#endif
