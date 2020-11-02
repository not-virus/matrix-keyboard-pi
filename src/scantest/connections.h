#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include <stddef.h>

#define COL_A 7
#define COL_B 8
#define COL_C 25
#define COL_D 24
#define COL_E 23
#define COL_F 18
#define COL_G 15
#define COL_H 14

#define ROW_1 16
#define ROW_2 20
#define ROW_3 21
#define ROW_4 26
#define ROW_5 19
#define ROW_6 13 // LED NUM
#define ROW_7 6
#define ROW_8 5
#define ROW_9 0  // LED SCRL
// #define ROW_10 ---
#define ROW_11 11
#define ROW_12 9
#define ROW_13 10
#define ROW_14 22
#define ROW_15 27 // LED CAPS
#define ROW_16 17
#define ROW_17 4
#define ROW_18 1
#define ROW_19 12

const size_t NUM_PINS = 26;
const unsigned short ALL_PINS[] = {COL_A, COL_B, COL_C, COL_D, COL_E, COL_F,
        COL_G, COL_H, ROW_1, ROW_2, ROW_3, ROW_4 , ROW_5, ROW_6, ROW_7, ROW_8,
        ROW_9, ROW_11, ROW_12, ROW_13, ROW_14, ROW_15, ROW_16, ROW_17, ROW_18,
        ROW_19};

const size_t NUM_COLS = 8;
const unsigned short COLS[] = {COL_A, COL_B, COL_C, COL_D, COL_E, COL_F, COL_G,
        COL_H};

const size_t NUM_ROWS = 15;
const unsigned short ROWS[] = {ROW_1, ROW_2, ROW_3, ROW_4 , ROW_5, ROW_7,
        ROW_8, ROW_11, ROW_12, ROW_13, ROW_14, ROW_16, ROW_17, ROW_18,
        ROW_19};

#endif
