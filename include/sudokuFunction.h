//
// Created by Pierre-Louis Demurger on 23/03/2021.
//

#ifndef SUDOKU_SUDOKUFUNCTION_H
    #define SUDOKU_SUDOKUFUNCTION_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <time.h>

typedef enum{
    TRUE=1,
    FALSE=0
}BOOL;

typedef struct{
    short *val_restante;
    short nb;
}value;

void init_sudoku(short **tab, short size);
void read_sudoku(short **tab, short size);
value get_value(short **tab, short i, short j, short size);
value get_value_2(short **tab, short i, short j, short size);
BOOL check_lign(short **tab, short i, short j, short tirrage);
BOOL check_col(short **tab, short i, short j, short tirrage);
BOOL check_case(short **tab, short i, short j, short tirrage, short size);
void create_sudoku_grid(short **tab, short size);
void blank_space(short **tab, short nb_blank, short size);
short no_zero(short **tab, short size);
BOOL resolve_sudoku(short **tab, short size);
void init_test_sudoku(short **tab);
void copy_sudoku(short **sudoku1, short **sudoku2, short size);
void create_sudoku(short **sudoku, short **sudoku_full, short size, short empty);

#endif //SUDOKU_SUDOKUFUNCTION_H
