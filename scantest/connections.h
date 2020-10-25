#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#define COL_A 14
#define COL_B 15
#define COL_C 18
#define COL_D 23
#define COL_E 24
#define COL_F 25
#define COL_G 8
#define COL_H 7

#define ROW_1 2
#define ROW_2 3
#define ROW_3 4
#define ROW_4 17
#define ROW_5 27
#define ROW_6 22
#define ROW_7 10
#define ROW_8 9
#define ROW_9 11
// #define ROW_10 ---
#define ROW_11 0
#define ROW_12 5
#define ROW_13 6
#define ROW_14 13
#define ROW_15 19
#define ROW_16 26
#define ROW_17 21
#define ROW_18 20
#define ROW_19 16

const size_t NUM_PINS = 26;
const int ALL_PINS[] = {COL_A, COL_B, COL_C, COL_D, COL_E, COL_F, COL_G, COL_H,
                        ROW_1, ROW_2, ROW_3, ROW_4 , ROW_5, ROW_6, ROW_7,
                        ROW_8, ROW_9, ROW_11, ROW_12, ROW_13, ROW_14, ROW_15,
                        ROW_16, ROW_17, ROW_18, ROW_19};

const size_t NUM_COLS = 8;
const int COLS[] = {COL_A, COL_B, COL_C, COL_D, COL_E, COL_F, COL_G, COL_H};

const size_t NUM_ROWS = 18;
const int ROWS[] = {ROW_1, ROW_2, ROW_3, ROW_4 , ROW_5, ROW_6, ROW_7, ROW_8,
                    ROW_9, ROW_11, ROW_12, ROW_13, ROW_14, ROW_15, ROW_16,
                    ROW_17, ROW_18, ROW_19};

#endif
